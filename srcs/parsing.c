/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:17:23 by chduong           #+#    #+#             */
/*   Updated: 2022/01/28 18:19:53 by chduong          ###   ########.fr       */
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
	if (s1 && !s2)
		ft_strlcpy(p, s1, len1 + 1);
	if (!s1 && s2)
		ft_strlcpy(p, s2, len2 + 1);
	else
	{
		ft_strlcpy(p, s1, len1 + 1);
		ft_strlcat(p, s2, len1 + len2 + 1);
	}
	return (p);
}

int	exec_cmd(char **arg, char *path)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		if(access(paths[i], X_OK))
	}
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