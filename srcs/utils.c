/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:54 by chduong           #+#    #+#             */
/*   Updated: 2022/03/31 13:07:36 by smagdela         ###   ########.fr       */
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
	{
		free(tab[i]);
		tab[i++] = NULL;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

t_list	*grep(t_list *env, char *varname)
{
	while (env)
	{
		if (ft_strcmp(env->var, varname) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
