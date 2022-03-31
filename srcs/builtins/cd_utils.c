/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:44:51 by chduong           #+#    #+#             */
/*   Updated: 2022/03/31 16:45:13 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char *newpwd, t_data *data)
{
	t_list	*pwd_env;
	
	pwd_env = grep("PWD", data);
	free(pwd_env->value);
	pwd_env->value = ft_strdup(newpwd);
	free(pwd_env->line);
	pwd_env->line = var_join("PWD", newpwd);
}