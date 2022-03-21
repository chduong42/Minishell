/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:42:25 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/09 18:00:31 by kennyduong       ###   ########.fr       */
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
            break ;
        }
        env = env->next;
	}
}

void	unset(char **arg, t_data *data)
{
    int		i;
	char	**tmp;

	i = 1;
	if (arg[1])
	{
		while (arg[i])
		{
			tmp = ft_split(arg[i], '=');
			del_var(tmp[0], data);
			free_tab(tmp);
		}
	}
}
