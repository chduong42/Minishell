/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:47:56 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/04 16:54:48 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				if (tmp->previous->out != -1)
					close(tmp->previous->out);
				tmp->previous->out = tmp->pipefd[1];
				if (tmp->next->in != -1)
					close(tmp->next->in);
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
			if (tmp->type == WORD && tmp->cmd != NULL && tmp->cmd[0])
				fork_exec(tmp, envp, data);
			tmp = tmp->next;
		}
	}
	if (data->token_list)
		free_toklist(&data->token_list);
	return (true);
}

char	*get_filepath(char **filename)
{
	char	*pwd;
	char	*filepath;

	if (*filename == NULL)
		return (NULL);
	if (*filename[0] == '/')
		return (*filename);
	pwd = getcwd(NULL, 0);
	filepath = path_join(pwd, *filename);
	free(pwd);
	pwd = NULL;
	free(*filename);
	*filename = NULL;
	return (filepath);
}
