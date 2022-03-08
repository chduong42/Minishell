/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:42:25 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/08 16:06:07 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **arg, t_data *data)
{
	(void)arg;
	(void)data;
	/*
    int		i;
	char	**tmp;
    t_list  *env;

	i = 1;
	env = data->env;
	if (arg[1])
	{
		while (arg[i])
		{
			tmp = ft_split(arg[i], '=');
	while (env)
	{
		if (ft_strcmp(arg[0], env->var) == 0)
        {
            ft_lstdelone(env, free);
            break ;
        }
        env = env->next;
	}
	*/
}
