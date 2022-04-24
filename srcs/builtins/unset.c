/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:42:25 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/24 21:05:21 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	print_error(char *varname)
{
	ft_putstr_fd("MiniShell: unset: `", 2);
	ft_putstr_fd(varname, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (false);
}

static bool	valid_varname(char *varname)
{
	int	i;

	if (varname[0] != '_' && !ft_isalpha(varname[0]))
		return (print_error(varname));
	i = 1;
	while (varname[i])
	{
		if (varname[i] != '_' && !ft_isalnum(varname[i]))
			return (print_error(varname));
		++i;
	}
	return (true);
}

static int	del_var(char *var, t_data *data)
{
	t_list	*env;

	env = grep(var, data);
	if (env && valid_varname(env->var))
	{
		if (ft_strncmp(env->var, "PATH", 5) == 0)
		{
			free_tab(data->path);
			data->path = NULL;
		}
		ft_lstdelone(env, free);
		return (1);
	}
	g_status = 1;
	return (0);
}

void	unset(char **arg, t_data *data)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (arg[i])
		n += del_var(arg[i++], data);
	if (n)
		update_env(data);
}
