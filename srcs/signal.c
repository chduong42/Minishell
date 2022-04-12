/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:08:28 by chduong           #+#    #+#             */
/*   Updated: 2022/04/12 18:58:36 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_action(int signo)
{
	if (signo == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 2);
	else if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_status = 130;
	}
}

static void	child_action(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		g_status = 131;
	}
	else if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_status = 130;
	}
}

void	sigctrl(int signo, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid > 0)
		parent_action(signo);
	else
		child_action(signo);
}
