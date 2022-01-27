/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/01/27 14:59:37 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	
	(void)env;
	line = NULL;
	if (ac == 1)
	{
		while (1)
		{
			line = readline("MiniShell >: ");
			if (line && *line)
        		add_history(line);
			if (parse_line(line))
				break ;
			free(line);
		}
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	clear_memory(line);
	return (0);
}
