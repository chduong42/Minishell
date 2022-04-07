/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:31 by chduong           #+#    #+#             */
/*   Updated: 2022/04/06 11:11:48 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns true if "cmd" is a builtin command, false otherwise.
*/
static bool	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (false);
	else if (!ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "unset", 6))
	{
		return (true);
	}
	return (false);
}

bool	exec_builtins(t_token *elem, t_data *data)
{
	if (is_builtin(elem->cmd[0]) == false)
		return (false);
	if (ft_strncmp(elem->cmd[0], "cd", 3) == 0)
		cd(elem->cmd[1], data);
	else if (ft_strncmp(elem->cmd[0], "echo", 5) == 0)
		echo(elem->cmd, data);
	else if (ft_strncmp(elem->cmd[0], "env", 4) == 0)
		env(data->env);
	else if (ft_strncmp(elem->cmd[0], "exit", 5) == 0)
		exit_ms(elem->cmd, data);
	else if (ft_strncmp(elem->cmd[0], "export", 7) == 0)
		export(elem->cmd, data);
	else if (ft_strncmp(elem->cmd[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(elem->cmd[0], "unset", 6) == 0)
		unset(elem->cmd, data);
	return (true);
}

static void	standalone_builtin_aux(t_token *elem, t_data *data,
									int *stdin_save, int *stdout_save)
{
	if (elem->in != -1)
	{
		*stdin_save = dup(0);
		if (*stdin_save == -1 || dup2(elem->in, 0) == -1)
			return (perror("MiniShell: Error"));
	}
	if (elem->out != -1)
	{
		*stdout_save = dup(1);
		if (*stdout_save == -1 || dup2(elem->out, 1) == -1)
			return (perror("MiniShell: Error"));
	}
	exec_builtins(elem, data);
}

static void	standalone_builtin(t_token *elem, t_data *data)
{
	int		stdin_save;
	int		stdout_save;

	standalone_builtin_aux(elem, data, &stdin_save, &stdout_save);
	if (elem->in != -1)
	{
		if (dup2(stdin_save, 0) == -1)
			return (perror("MiniShell: Error"));
		close(elem->in);
		close(stdin_save);
		elem->in = -1;
	}
	if (elem->out != -1)
	{
		if (dup2(stdout_save, 1) == -1)
			return (perror("MiniShell: Error"));
		close(elem->out);
		close(stdout_save);
		elem->out = -1;
	}
}

void	fork_exec(t_token *elem, char **envp, t_data *data)
{
	pid_t	pid;
	int		wstatus;

	if (in_pipeline(elem) == false && is_builtin(elem->cmd[0]) == true)
		return (standalone_builtin(elem, data));
	pid = fork();
	if (pid < 0)
		return (perror("MiniShell: Error"));
	else if (pid == 0)
		for_child(elem, data, envp);
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
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) || WIFSIGNALED(wstatus))
		data->status = WEXITSTATUS(wstatus);
}
