/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/02/01 16:40:41 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*grep_path(char **env)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		++i;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**path;
	
	line = NULL;
	if (ac == 1)
	{
		path = ft_split(grep_path(env), ':');
		while (1)
		{
			line = readline("Minishell$> ");
			if (line && *line)
        		add_history(line);
			parse_line(line, path, env);
			free(line);
		}
		clear_memory(line, path);
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	return (0);
}
