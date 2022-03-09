/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:54 by chduong           #+#    #+#             */
/*   Updated: 2022/03/09 12:35:40 by smagdela         ###   ########.fr       */
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

char	*grep_path(t_list *env)
{
	while (env)
	{
		if (ft_strncmp(env->line, "PATH=", 5) == 0)
			return (env->line + 5);
		env = env->next;
	}
	return (NULL);
}
