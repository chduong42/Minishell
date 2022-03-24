/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:51:21 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/24 13:08:55 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(char **arg, int nl)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("%s", arg[i++]);
		if (arg[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
}

int	check_nflag(char *str)
{
	if (strncmp(str, "-n", 2) == 0)
	{
		++str;
		while (*str == 'n')
			++str;
		if (*str == '\0')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void	echo(char **arg)
{
	if (arg[1] == NULL)
		ft_putchar_fd('\n', 1);
	else if (check_nflag(arg[1]))
	{
		if (arg[2] == NULL)
			return ;
		else
			print_echo(arg + 2, 0);
	}
	else
		print_echo(arg + 1, 1);
}
