/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:31 by chduong           #+#    #+#             */
/*   Updated: 2022/04/01 15:57:45 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	builtins(t_token *elem, t_data *data)
{
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
	else
		return (false);
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

	if (in_pipeline(elem) == false && builtins(elem, data) == true)
		return ;
	pid = fork();
	if (pid < 0)
		return (perror("MiniShell: Fork failed."));
	else if (pid == 0)
	{
		if (elem->in != -1)
			dup2(elem->in, 0);
		if (elem->out != -1)
			dup2(elem->out, 1);
		if (builtins(elem, data) == true)
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
