/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:47:56 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/30 18:04:27 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_filepath(char *filename)
{
	char	*pwd;
	char	*filepath;

	if (filename == NULL)
		return (NULL);
	if (filename[0] == '/')
		return (filename);
	pwd = getcwd(NULL, 0);
	filepath = path_join(pwd, filename);
	free(pwd);
	free(filename);
	return (filepath);
}

static void	file_handler(t_data *data)
{
	t_token	*tmp;
	char	*filepath;
	int		fd;

	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == LESS)
		{
			filepath = get_filepath(pop_first_cmd(tmp->next));
			if (access(filepath, R_OK) == 0)
			{
				fd = open(filepath, O_RDONLY);
				if (tmp->previous == NULL)
					tmp->next->in = fd;
				else
					tmp->previous->in = fd;
//				When close() ?
			}
			else
				perror("Minishell: Error");
			free(filepath);
			filepath = NULL;
		}
		else if (tmp->type == GREAT)
		{
			filepath = get_filepath(pop_last_cmd(tmp->next));
			if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
			{
				fd = open(filepath, O_WRONLY | O_CREAT);
				tmp->previous->out = fd;
//				When close() ?
			}
			else
				perror("Minishell: Error");
			free(filepath);
			filepath = NULL;
		}
/*		else if (tmp->type == DLESS)
		{
			heredoc(pop_first_cmd(tmp->next));
		}*/
		else if (tmp->type == DGREAT)
		{
			filepath = get_filepath(pop_last_cmd(tmp->next));
			if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
			{
				fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND);
				tmp->previous->out = fd;
//				When close() ?
			}
			else
				perror("Minishell: Error");
			free(filepath);
			filepath = NULL;
		}
		tmp = tmp->next;
	}
}

/*
Reproduce the behavior of multiple pipes, adding file redirectors too.
*/
static void	redirection_handler(char **envp, t_data *data)
{
	t_token	*tmp;

	file_handler(data);
	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (pipe(tmp->pipefd) == -1)
				perror("MiniShell: Pipe failed");
			else
			{
				tmp->previous->out = tmp->pipefd[1];
				tmp->next->in = tmp->pipefd[0];
			}
		}
		tmp = tmp->next;
	}
	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == WORD)
			fork_exec(tmp, envp, data);
		tmp = tmp->next;
	}
}

/*
Launch the execution of the whole token_list, and frees it.
*/
bool	executor(char **envp, t_data *data)
{
	if (data->token_list == NULL)
		return (false);
	if (data->token_list->next == NULL)
		fork_exec(data->token_list, envp, data);
	else
		redirection_handler(envp, data);
	if (data->token_list)
		free_toklist(&data->token_list);
	return (true);
}
