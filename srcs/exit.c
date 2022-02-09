/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:08:07 by chduong           #+#    #+#             */
/*   Updated: 2022/02/09 17:15:36 by chduong          ###   ########.fr       */
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

void	free_exit(char **arg, char *line, char **path, int opt)
{
	if (arg)
		free_tab(arg);
	if (path)
		free_tab(path);
	if (line)
		free(line);
	clear_history();
	rl_clear_history();
	exit(opt);
}

void	exit_shell(char **arg, char *line, char **path)
{
	int	nb_arg;

	nb_arg = count_str(arg);
	if (nb_arg == 1)
		free_exit(arg, line, path, EXIT_SUCCESS);
	else if (nb_arg == 2)
	{
		if (only_digit(arg[1]))
			free_exit(arg, line, path, ft_atoi(arg[1]));
		else
		{
			printf("Minishell: exit: %s: numeric argument required\n", arg[1]);
			free_exit(arg, line, path, EXIT_SUCCESS);
		}
	}
	else
		printf("Minishell: exit: too many argument\n");
}