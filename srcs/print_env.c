/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:47:38 by chduong           #+#    #+#             */
/*   Updated: 2022/03/25 15:54:17 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env)
{
	while (env)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
}

static char	**cpy_env(t_list *env)
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

static void	sort_export(char **sort)
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

void	print_export(t_data *data)
{
	int	i;

	if (data->newenv && data->export)
	{
		free_tab(data->export);
		data->export = NULL;
		data->newenv = false;
	}
	if (!data->export)
	{
		data->export = cpy_env(data->env);
		sort_export(data->export);	
	}
	i = 0;
	while (data->export[i])
		printf("%s\n", data->export[i++]);
}
