/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:54 by chduong           #+#    #+#             */
/*   Updated: 2022/02/08 18:37:31 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		++i;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

void	clear_memory(char *line, char **path)
{
	free_tab(path);
	if (line)
	{
		free(line);
		line = NULL;
	}
	clear_history();
	rl_clear_history();
}
