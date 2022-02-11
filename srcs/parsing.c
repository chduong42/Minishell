/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:17:23 by chduong           #+#    #+#             */
/*   Updated: 2022/02/11 17:22:50 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options*/

void	parse_line(char *line, char **path, char **env)
{
	char	**arg;
	pid_t	pid;

	arg = ft_split(line, ' ');
	if (ft_strncmp(arg[0], "exit", 5) == 0)
		exit_shell(arg, line, path);
	else
	{
		pid = fork();
		if (pid == 0)
			exec_cmd(arg, path, env);
		else
			wait(0);
	}
}
