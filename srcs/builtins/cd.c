/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:51:15 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/04 18:36:00 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_data *data)
{
	t_list	*old;
	t_list	*pwd;
	char	*tmp;

	pwd = grep("PWD", data);
	old = grep("OLDPWD", data);
	if (old)
	{
		free(old->value);
		free(old->line);
		old->value = ft_strdup(pwd->value);
		old->line = var_join("OLDPWD", pwd->value);
	}
	else
	{
		tmp = var_join("OLDPWD", pwd->value);
		ft_lstadd_back(&data->env, ft_lstnew(tmp, "OLDPWD", pwd->value));
		free(tmp);
	}
}

void	update_pwd(char *path, t_data *data)
{
	char	*newpwd;
	t_list	*pwd_env;

	if (data->status == 0)
	{
		newpwd = getcwd(NULL, 0);
		pwd_env = grep("PWD", data);
		free(pwd_env->line);
		pwd_env->line = var_join("PWD", newpwd);
		free(pwd_env->value);
		pwd_env->value = ft_strdup(newpwd);
		free(newpwd);
	}
	else
		printf("Minishell: cd: %s: %s\n", path, strerror(errno));
}

void	go_home(t_data *data)
{
	t_list	*env;

	env = grep("HOME", data);
	if (env)
	{
		data->status = chdir(env->value) * -1;
		update_pwd(env->value, data);
	}
	else
	{
		printf("Minishell: cd: HOME not set\n");
		data->status = 1;
	}
}

void	cd(char *path, t_data *data)
{
	update_oldpwd(data);
	if (!path)
		go_home(data);
	else
	{
		data->status = chdir(path) * -1;
		update_pwd(path, data);
	}
	update_env(data);
}
