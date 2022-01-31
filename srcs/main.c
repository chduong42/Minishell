/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/01/31 15:41:18 by chduong          ###   ########.fr       */
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

void	clear_memory(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	clear_history();
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*path;
	
	line = NULL;
	path = grep_path(env);
	if (ac == 1)
	{
		while (1)
		{
			line = readline("MiniShell >: ");
			if (line && *line)
        		add_history(line);
			if (parse_line(line, path, env))
				break ;
			free(line);
		}
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	clear_memory(line);
	return (0);
}
