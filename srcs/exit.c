/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:08:07 by chduong           #+#    #+#             */
/*   Updated: 2022/01/28 15:19:40 by chduong          ###   ########.fr       */
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

void	exit_shell(char **arg)
{
	int	nb_arg;

	nb_arg = count_arg(arg);
	if (nb_arg == 1)
		exit(EXIT_SUCCESS);
	else if (nb_arg == 2)
	{
		if (only_digit(arg[1]))
			exit(ft_atoi(arg[1]));
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", arg[1]);
			exit(EXIT_SUCCESS);
		}
	}
	else
		printf("minishell: exit: too many argument\n");
}