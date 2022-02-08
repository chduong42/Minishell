/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/02/08 21:43:37 by smagdela         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**path;
	t_token	*token_list;

	line = NULL;
	if (ac == 1)
	{
		path = ft_split(grep_path(env), ':');
		ft_print_title();
		while (1)
		{
			line = readline("\e[1;35mMiniShell >: \e[0m");
			if (line && *line)
				add_history(line);
			token_list = lexer(line);
			display_n_free(token_list);
		}
		free_tab(path);
		clear_history();
		rl_clear_history();
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	return (0);
}
