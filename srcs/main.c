/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/03/25 17:08:37 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac == 1)
	{
		data_init(&data, envp);
		ft_print_title();
		while (1)
		{
			data.line = readline(PROMPT);
			if (data.line && *data.line)
			{
				add_history(data.line);
				data.token_list = lexer(data.line);
				data.line = NULL;
				if (data.token_list != NULL)
				{
//					printf("\n	\e[0;33m\e[4;33mTokenizer output :\e[0m\n\n");
//					display_toklist(data.token_list);
					data.token_list = analyzer(data.token_list, &data);
					if (data.token_list != NULL)
					{
//						printf("\n	\e[0;33m\e[4;33mAnalyzer output :\e[0m\n\n");
//						display_toklist(data.token_list);
//						printf("\n----------------------------------------\n");
						executor(data.token_list, envp, &data);
					}
				}
			}
		}
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	return (0);
}
