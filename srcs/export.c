/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:11:03 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/05 20:15:31 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_new_var(char *str, t_data *data)
{
	t_list *env;

	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->var, str) == 0)
			return (false);
		env = env->next;
	}
	return (true);
}

void	change_var(char *str, t_data *data)
{
	
}

void	export(char **arg, t_data *data)
{
	int		i;
	char	**tmp;

	i = 1;
	if (arg[1])
	{
		while (arg[i])
		{
			if (is_new_var(arg[i], data))
			{
				tmp = ft_split(arg[i], '=');
				ft_lstadd_back(data->env, ft_lstnew(arg[i], tmp[0], tmp[1]));
				free_tab(tmp);
			}
			else
				change_var(arg[i], data);
		}
		data->newenv = true;
	}
	else
		print_export(data);
}
