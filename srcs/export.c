/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:11:03 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/24 13:56:06 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_new_var(char *var, t_data *data)
{
	t_list *env;

	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->var, var) == 0)
			return (false);
		env = env->next;
	}
	return (true);
}

void	change_var(char *envl, char **arg, t_data *data)
{
	t_list *env;

	env = data->env;
	while (env)
	{
		if (ft_strcmp(arg[0], env->var) == 0)
		{
			free(env->line);
			env->line = ft_strdup(envl);
			free(env->content);
			env->content = ft_strdup(arg[1]);
			break ;
		}
		env = env->next;
	}
}

void	export(char **arg, t_data *data)
{
	int		i;
	char	**tmp;

	if (arg[1])
	{
		i = 1;
		while (arg[i])
		{
			tmp = ft_split(arg[i], '=');
			if (is_new_var(tmp[0], data))
				ft_lstadd_back(&data->env, ft_lstnew(arg[1], tmp[0], tmp[1]));
			else
				change_var(arg[i], tmp, data);
			free_tab(tmp);
			++i;
		}
		data->newenv = true;
	}
	else
		print_export(data);
}
