/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/03/14 16:37:16 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	data_init(t_data *data, char **envp)
{
	int		i;
	char	**tmp;

	data->newenv = 0;
	data->newpath = 0;
	data->export = NULL;
	data->line = NULL;
	data->env = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		/*
		printf("%s\n", envp[i]);
		printf("%s\n", tmp[0]);
		printf("%s\n", tmp[1]);
		*/
		ft_lstadd_back(&data->env,
			ft_lstnew(ft_strdup(envp[i]), tmp[0], tmp[1]));
		//free_tab(tmp);
		++i;
	}
	data->path = ft_split(grep_path(data->env), ':');
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_token	*token_list;

	if (ac == 1)
	{
		data_init(&data, envp);
		/*Print envp
		tmp = data.env;
		while (tmp)
		{
			printf("%s=%s\n", tmp->var, tmp->content);
			tmp = tmp->next;
		}
		*/
		ft_print_title();
		while (1)
		{
			data.line = readline("\e[1;35mMiniShell >: \e[0m");
			if (data.line && *data.line)
			{
				add_history(data.line);
				token_list = lexer(data.line);
				printf("\n	\e[0;33m\e[4;33mTokenizer output :\e[0m\n\n");
				display_toklist(token_list);
				token_list = analyzer(token_list, &data);
				if (token_list != NULL)
				{
					printf("\n	\e[0;33m\e[4;33mAnalyzer output :\e[0m\n\n");
					display_toklist(token_list);
					printf("\n");
					free_toklist(token_list);
				}
				//parse_line(envp, &data);
				//free(data.line);
				data.line = NULL;
			}
		}
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	return (0);
}
