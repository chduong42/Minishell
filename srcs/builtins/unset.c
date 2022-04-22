/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:42:25 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/22 17:01:54 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var(char *var, t_data *data)
{
	t_list	*env;

	env = grep(var, data);
	if (env && ft_strncmp(env->var, "PATH", 5) == 0)
	{
		free_tab(data->path);
		data->path = NULL;
	}
	ft_lstdelone(env, free);
}

void	unset(char **arg, t_data *data)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (valid_varname(arg[i]))
			del_var(arg[i], data);
		else
			g_status = 1;
		++i;
	}
	if (arg[1])
		update_env(data);
}
