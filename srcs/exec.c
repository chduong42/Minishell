/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:31 by chduong           #+#    #+#             */
/*   Updated: 2022/03/21 16:55:01 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_join(char *path, char *cmd)
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
	int		i;

	i = 0;
	while (data->path[i])
	{
		cmd = path_join(data->path[i], arg[0]);
		if (access(cmd, X_OK) == 0)
			execve(cmd, arg, envp);
		free(cmd);
		++i;
	}
	cmd = path_join(getcwd(NULL, 0), arg[0]);
	if (access(cmd, X_OK) == 0)
		execve(cmd, arg, envp);
	free(cmd);
	perror("Error");
}

void	fork_exec(char **arg, char **envp, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_cmd(arg, envp, data);
	else
		wait(0);
}
