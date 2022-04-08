/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:08:28 by chduong           #+#    #+#             */
/*   Updated: 2022/04/08 18:08:57 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int signo, siginfo_t *info, void *context)
{
	(void)context;

	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		if (info->si_pid > 0)
			rl_redisplay();
	}
}

void	sigquit(int signo)
{
	(void)signo;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	exit(131);
}
