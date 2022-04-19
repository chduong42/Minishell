/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:08:28 by chduong           #+#    #+#             */
/*   Updated: 2022/04/15 16:40:50 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(void)
{
	signal(SIGINT, sighand);
	signal(SIGQUIT, sighand);
	signal(SIGTERM, SIG_IGN);
}

void	set_signal2(void)
{
	signal(SIGINT, sighand2);
	signal(SIGQUIT, sighand2);
	signal(SIGSEGV, sighand2);
}

void	set_signal3(void)
{
	signal(SIGINT, sighand3);
}
