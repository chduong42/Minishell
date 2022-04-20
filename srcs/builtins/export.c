/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:11:03 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/20 15:27:09 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_new_var(char *var, t_data *data)
{
	t_list	*env;

	env = grep(var, data);
	if (!env)
		return (true);
	else
		return (false);
}

static void	change_var(char *envl, char **arg, t_data *data)
{
	t_list	*env;

	env = grep(arg[0], data);
	free(env->line);
	env->line = ft_strdup(envl);
	free(env->value);
	if (arg[1])
		env->value = ft_strdup(arg[1]);
	else
		env->value = NULL;
}

static void	print_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->export[i])
		printf("%s\n", data->export[i++]);
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
			if (ft_strncmp(tmp[0], "PATH", 5) == 0)
				data->newpath = true;
			if (is_new_var(tmp[0], data))
				ft_lstadd_back(&data->env, ft_lstnew(arg[i], tmp[0], tmp[1]));
			else
				change_var(arg[i], tmp, data);
			free_tab(tmp);
			++i;
		}
		update_env(data);
	}
	else
		print_export(data);
	g_status = 0;
}
