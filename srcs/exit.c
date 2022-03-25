/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:08:07 by chduong           #+#    #+#             */
/*   Updated: 2022/03/25 16:57:36 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_digit(char *arg)
{
	if (*arg == '-')
		return (1);
	if (*arg == '+')
		++arg;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static void	free_exit(char **arg, t_data *data, int opt)
{
	if (arg)
		free_tab(arg);
	printf("free arg\n");
	if (data->line)
		free(data->line);
	printf("free line\n");
	if (data->path)
		free_tab(data->path);
	printf("free path\n");
	if (data->export)
		free_tab(data->export);
	printf("free export\n");
	if (data->env)
		ft_lstclear(&data->env, free);
	printf("lstclear env\n");
	if (data->token_list)
		free_toklist(data->token_list);
	printf("free tokenlist\n");
	rl_clear_history();
	printf("clear history\n");
	exit(opt);
}

void	exit_ms(char **arg, t_data *data)
{
	int	nb_arg;

	nb_arg = count_str(arg);
	if (nb_arg == 1)
		free_exit(arg, data, EXIT_SUCCESS);
	else if (nb_arg == 2)
	{
		if (only_digit(arg[1]))
			free_exit(arg, data, ft_atoi(arg[1]));
		else
		{
			printf("Minishell: exit: %s: numeric argument required\n", arg[1]);
			free_exit(arg, data, EXIT_SUCCESS);
		}
	}
	else
		printf("Minishell: exit: too many argument\n");
}
