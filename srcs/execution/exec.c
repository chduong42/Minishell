/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:31 by chduong           #+#    #+#             */
/*   Updated: 2022/04/08 17:30:45 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_exec_aux(t_token *elem)
{
	if (elem->in != -1)
	{
		close(elem->in);
		elem->in = -1;
		if (elem->previous && elem->previous->type == PIPE)
			close(elem->previous->pipefd[0]);
	}
	if (elem->out != -1)
	{
		close(elem->out);
		elem->out = -1;
		if (elem->next && elem->next->type == PIPE)
			close(elem->next->pipefd[1]);
	}
}

pid_t	fork_exec(t_token *elem, char **envp, t_data *data)
{
	pid_t	pid;

	if (in_pipeline(elem) == false && is_builtin(elem->cmd[0]) == true)
	{
		standalone_builtin(elem, data);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("MiniShell: Error");
		return (-1);
	}
	else if (pid == 0)
		for_child(elem, data, envp);
	fork_exec_aux(elem);
	return (pid);
}
