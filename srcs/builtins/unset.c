/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:42:25 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/06 11:56:48 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var(char *var, t_data *data)
{
	t_list	*env;

	env = grep(var, data);
	ft_lstdelone(env, free);
}

void	unset(char **arg, t_data *data)
{
	int	i;

	i = 1;
	while (arg[i])
		del_var(arg[i++], data);
	if (arg[1])
		update_env(data);
}
