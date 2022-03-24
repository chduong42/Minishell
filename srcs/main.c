/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/03/24 15:38:11 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_token	*token_list;

	if (ac == 1)
	{
		data_init(&data, envp);
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
					printf("\n--------------------------------------------\n");
					executor(token_list, envp, &data);
				}
			}
		}
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	return (0);
}
