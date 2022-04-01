/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:47:56 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/01 16:10:48 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	file_handler(t_data *data)
{
	t_token	*tmp;
	char	*filepath;
	int		fd;

	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == LESS && tmp->cmd != NULL)
		{
			filepath = get_filepath(&tmp->cmd[0]);
			if (access(filepath, R_OK) == 0)
			{
				fd = open(filepath, O_RDONLY);
				if (tmp->previous == NULL)
				{
					if (tmp->next->in != -1)
						close(tmp->next->in);
					tmp->next->in = fd;
				}
				else
				{
					if (tmp->previous->in != -1)
						close(tmp->previous->in);
					tmp->previous->in = fd;
				}
			}
			else
				perror("MiniShell: Error");
			free(filepath);
			filepath = NULL;
		}
		else if (tmp->type == GREAT && tmp->cmd != NULL)
		{
			filepath = get_filepath(&tmp->cmd[0]);
			if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
			{
				fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if (tmp->previous->out != -1)
					close(tmp->previous->out);
				tmp->previous->out = fd;
			}
			else
				perror("MiniShell: Error");
			free(filepath);
			filepath = NULL;
		}
/*		else if (tmp->type == DLESS && tmp->cmd != NULL)
		{
			heredoc(tmp->cmd[0]);
		}*/
		else if (tmp->type == DGREAT && tmp->cmd != NULL)
		{
			filepath = get_filepath(&tmp->cmd[0]);
			if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
			{
				fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0666);
				if (tmp->previous->out != -1)
					close(tmp->previous->out);
				tmp->previous->out = fd;
			}
			else
				perror("MiniShell: Error");
			free(filepath);
			filepath = NULL;
		}
		tmp = tmp->next;
	}
}

static void	pipe_handler(t_data *data)
{
	t_token	*tmp;

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
}

/*
Launch the execution of the whole token_list, and frees it.
Reproduce the behavior of multiple pipes, adding file redirectors too.
*/
bool	executor(char **envp, t_data *data)
{
	t_token	*tmp;

	if (data->token_list == NULL)
		return (false);
	if (data->token_list->next == NULL)
		fork_exec(data->token_list, envp, data);
	else
	{
		file_handler(data);
		pipe_handler(data);
		tmp = data->token_list;
		while (tmp)
		{
			if (tmp->type == WORD && tmp->cmd != NULL && tmp->cmd[0] != NULL)
				fork_exec(tmp, envp, data);
			tmp = tmp->next;
		}
	}
	if (data->token_list)
		free_toklist(&data->token_list);
	return (true);
}
