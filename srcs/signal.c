/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:08:28 by chduong           #+#    #+#             */
/*   Updated: 2022/04/21 18:55:41 by chduong          ###   ########.fr       */
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
		rl_replace_line("", 0);
		close(STDIN_FILENO);
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
	}
	else if (mode == RESET)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
	}
	else if (mode == HEREDOC)
		signal(SIGINT, heredoc_hdl);
}
