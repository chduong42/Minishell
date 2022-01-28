/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:17:23 by chduong           #+#    #+#             */
/*   Updated: 2022/01/28 17:42:57 by chduong          ###   ########.fr       */
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

int	exec_cmd(char **arg, char *path)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
		access(paths[i], )
}

int	parse_line(const char *line, char *path)
{
	char	**arg;

	arg = ft_split(line, ' ');
	(void)path;
	if (ft_strncmp(arg[0], "exit", 5) == 0)
		exit_shell(arg);
	return (0);
}