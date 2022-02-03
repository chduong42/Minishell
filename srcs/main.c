/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/02/03 14:23:27 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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
	t_token	*token_list;
	t_token	*tmp;

	line = NULL;
	path = grep_path(env);
	if (ac == 1)
	{
		while (1)
		{
			line = readline("MiniShell >: ");
			if (line && *line)
				add_history(line);
			token_list = lexer(line);
			if (token_list == NULL)
				ft_putstr_fd("Error : lexer failed\n", 2);
			else
			{
				tmp = token_list;
				while (tmp != NULL)
				{
					printf("%s => %d\n", tmp->data, tmp->type);
					tmp = tmp->next;
				}
				free_toklist(token_list);
			}
			free(line);
		}
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	clear_memory(line);
	return (0);
}
