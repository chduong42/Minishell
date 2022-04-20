/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:08:28 by chduong           #+#    #+#             */
/*   Updated: 2022/04/20 15:51:02 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	default_hdl(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 130;
		if (write(1, "\n", 1) == -1)
			perror(__func__);
		rl_replace_line("", 0);
		if (rl_on_new_line())
			perror(__func__);
		rl_redisplay();
	}
}

static void	heredoc_hdl(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 130;
		if (write(1, "\n", 1) == -1)
			perror("");
		rl_replace_line("", 0);
		if (close(STDIN_FILENO) == -1)
			perror("");
	}
}

void	set_signal(int mode)
{
	if (mode == DEFAULT)
	{
		signal(SIGINT, default_hdl);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
	}
	else if (mode == MUTE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
	}
	else if (mode == RESET)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
	}
	else if (mode == HEREDOC)
		signal(SIGINT, heredoc_hdl);
}

void	sighand2(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_status = 131;
	}
	else if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_status = 130;
	}
	else if (signo == SIGSEGV)
	{
		ft_putstr_fd("Segmentation fault (core dumped)\n", 2);
		g_status = 139;
	}
}
