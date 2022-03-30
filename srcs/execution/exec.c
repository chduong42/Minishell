/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:31 by chduong           #+#    #+#             */
/*   Updated: 2022/03/30 18:49:36 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	builtins(t_token *elem, t_data *data)
{
	if (ft_strncmp(elem->cmd[0], "cd", 3) == 0)
		cd();
	else if (ft_strncmp(elem->cmd[0], "echo", 5) == 0)
		echo(elem->cmd);
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

char	*path_join(char *path, char *cmd)
{
	char	*p;
	int		len1;
	int		len2;

	if (!path || !cmd)
		return (NULL);
	len1 = ft_strlen(path);
	len2 = ft_strlen(cmd);
	p = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!p)
		return (NULL);
	ft_strlcpy(p, path, len1 + 1);
	ft_strlcat(p, "/", len1 + 2);
	ft_strlcat(p, cmd, len1 + len2 + 2);
	return (p);
}

static void	exec_cmd(char **arg, char **envp, t_data *data)
{
	char	*cmd;
	char	*pwd;
	int		i;

	cmd = get_binpath(arg[0], data);
	if (access(cmd, X_OK) == 0)
		execve(cmd, arg, envp);
	free(cmd);
	perror("MiniShell: Error");
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
		return (perror("Fork failed."));
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
		close(elem->in);
	if (elem->out != -1)
		close(elem->out);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) == true)
		data->status = WEXITSTATUS(wstatus);
}
