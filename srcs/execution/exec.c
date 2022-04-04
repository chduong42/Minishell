/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:31 by chduong           #+#    #+#             */
/*   Updated: 2022/04/04 16:39:37 by smagdela         ###   ########.fr       */
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
/*	else if (ft_strncmp(cmd, "cd", 3) == 0)*/
	else if (!ft_strncmp(cmd, "echo", 5)
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

static bool	exec_builtins(t_token *elem, t_data *data)
{
	if (is_builtin(elem->cmd[0]) == false)
		return (false);
/*	if (ft_strncmp(elem->cmd[0], "cd", 3) == 0)
		cd(elem->cmd[1], data);*/
	if (ft_strncmp(elem->cmd[0], "echo", 5) == 0)
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

static void	exec_cmd(char **arg, char **envp, t_data *data)
{
	char	*cmd;

	cmd = get_binpath(arg[0], data);
	if (access(cmd, X_OK) == 0)
		execve(cmd, arg, envp);
	perror("MiniShell: Error");
	free(cmd);
	free_exit(data, 127);
}

static bool	in_pipeline(t_token *elem)
{
	if (elem == NULL)
		return (false);
	if (elem->previous == NULL || elem->previous->type != PIPE)
	{
		if (elem->next == NULL || elem->next->type != PIPE)
			return (false);
	}
	return (true);
}

void	fork_exec(t_token *elem, char **envp, t_data *data)
{
	pid_t	pid;
	int		wstatus;
	int		stdin_save;
	int		stdout_save;

	if (in_pipeline(elem) == false && is_builtin(elem->cmd[0]) == true)
	{
		if (elem->in != -1)
		{
			stdin_save = dup(0);
			if (stdin_save == -1 || dup2(elem->in, 0) == -1)
				return (perror("MiniShell: Error"));
		}
		if (elem->out != -1)
		{
			stdout_save = dup(1);
			if (stdout_save == -1 || dup2(elem->out, 1) == -1)
				return (perror("MiniShell: Error"));
		}
		exec_builtins(elem, data);
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
		return ;
	}
	pid = fork();
	if (pid < 0)
		return (perror("MiniShell: Error"));
	else if (pid == 0)
	{
		if (elem->in != -1)
			if (dup2(elem->in, 0) == -1)
				return (perror("MiniShell: Error"));
		if (elem->out != -1)
			if (dup2(elem->out, 1) == -1)
				return (perror("MiniShell: Error"));
		if (exec_builtins(elem, data) == true)
			free_exit(data, EXIT_SUCCESS);
		exec_cmd(elem->cmd, envp, data);
	}
	if (elem->in != -1)
	{
		close(elem->in);
		elem->in = -1;
	}
	if (elem->out != -1)
	{
		close(elem->out);
		elem->out = -1;
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) || WIFSIGNALED(wstatus))
		data->status = WEXITSTATUS(wstatus);
}
