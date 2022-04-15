/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:24:02 by chduong           #+#    #+#             */
/*   Updated: 2022/04/15 16:25:24 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sigctrl;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);*/

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
	// else if (signo == SIGSEGV)
	// {
	// 	ft_putstr_fd("SEGFAULT: (core dumped)\n", 2);
	// 	g_status = 139;
	// }
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