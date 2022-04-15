/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:21:41 by chduong           #+#    #+#             */
/*   Updated: 2022/04/15 19:09:19 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighand(int signo)
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

void	sighand2(int signo)
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
	else if (signo == SIGSEGV)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		g_status = 139;
	}
}

void	sighand3(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 130;
		close(STDIN_FILENO);
	}
}
