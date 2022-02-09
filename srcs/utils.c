/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:54 by chduong           #+#    #+#             */
/*   Updated: 2022/02/09 13:53:25 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
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