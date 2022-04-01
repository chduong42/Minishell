/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:11:03 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/01 13:06:57 by kennyduong       ###   ########.fr       */
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
	if (ft_strncmp(arg[0], "PATH", 5) == 0)
		data->newpath = true;
	free(env->line);
	env->line = ft_strdup(envl);
	free(env->value);
	if (arg[1])
		env->value = ft_strdup(arg[1]);
	else
		env->value = NULL;
}

void	print_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->export[i])
		printf("%s\n", data->export[i++]);
}

void update_env(t_data *data)
{
	t_list *path;

	if (data->newenv == true)
	{
		free(data->export);
		data->export = NULL;
		data->export = cpy_env(data->env);
		sort_export(data->export);
		data->newenv = false;
	}
	if (data->newpath == true)
	{
		path = grep("PATH", data);
		free_tab(data->path);
		data->path = NULL;
		data->path = ft_split(path->value,':');
		data->newpath = false;
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
				ft_lstadd_back(&data->env, ft_lstnew(arg[i], tmp[0], tmp[1]));
			else
				change_var(arg[i], tmp, data);
			free_tab(tmp);
			++i;
		}
		data->newenv = true;
	}
	else
		print_export(data);
	update_env(data);
}
