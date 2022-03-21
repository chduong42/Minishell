/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:51:21 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/21 16:33:12 by chduong          ###   ########.fr       */
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

void	echo(char **arg)
{
	if (arg[1] == NULL)
		ft_putchar_fd('\n', 1);
	else if (strncmp(arg[1], "-n", 3) == 0)
	{
		if (arg[2] == NULL)
			return ;
		else
			print_echo(arg + 2, 0);
	}
	else
		print_echo(arg + 1, 1);
}
