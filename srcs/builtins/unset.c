/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:42:25 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/25 11:26:46 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var(char *var, t_data *data)
{
    t_list  *env;

	env = data->env;
	while (env)
	{
		if (ft_strcmp(var, env->var) == 0)
        {
            ft_lstdelone(env, free);
            return ;
        }
        env = env->next;
	}
}

void	unset(char **arg, t_data *data)
{
    int		i;

	i = 1;
	while (arg[i])
		del_var(arg[i++], data);
}
