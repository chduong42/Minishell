/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:31:59 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/25 11:09:48 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_env(t_list *env)
{
	char	**sort;
	int		i;
	
	sort = malloc(sizeof(char*) * (ft_lstsize(env) + 1));
	i = 0;
	while (env)
	{
		sort[i] = env->line;
		env = env->next;
		++i;
	}
	sort[i] = 0;
	return (sort);
}

void	sort_export(char **sort)
{
	char	*tmp;
	int		i;
	int		j;
	
	i = 0;
	while (sort[i])
	{
		j = i + 1;
		while (sort[j])
		{
			if (ft_strcmp(sort[i], sort[j]) > 0)
			{
				tmp = sort[i];
				sort[i] = sort[j];
				sort[j] = tmp;
			}
			++j;
		}
		++i;
	}
}

void	new_export(t_data *data)
{
	if (data->newenv)
	{
		free_tab(data->export);
		data->export = NULL;
		data->export = cpy_env(data->env);
		data->newenv = false;
	}
}

void	new_path(t_data *data)
{
	if (data->newpath)
	{
		free_tab(data->path);
		data->path = NULL;
		data->path = ft_split(getenv("PATH"), ':');
		data->newpath = false;
	}
}
