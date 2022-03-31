/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:51:15 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/31 18:12:23 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char *newpwd, t_data *data)
{
	t_list	*pwd_env;
	
	pwd_env = grep("PWD", data);
	free(pwd_env->line);
	pwd_env->line = var_join("PWD", newpwd);
	free(pwd_env->value);
	pwd_env->value = ft_strdup(newpwd);
}

void	go_home(t_data *data)
{
	char 	*tmp;
	
	tmp = getenv("HOME");
	if (tmp)
		data->status = chdir(tmp) * -1;
	else
	{
		printf("Minishell: cd: HOME not set\n");
		data->status = 1;
	}
	if (data->status == 0)
		update_pwd(tmp, data);
}

void	go_back(t_data *data)
{
	int		i;
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	i = 0;
	while (cwd[i])
		++i;
	while (cwd[i] != '/')
		--i;
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, cwd, i + 1);
	free(cwd);
	data->status = chdir(tmp) * -1;
	if (data->status == 0)
		update_pwd(tmp, data);
	free(tmp);
}

void	update_oldpwd(t_data *data)
{
	t_list	*old;
	t_list	*pwd;
	
	pwd = grep("PWD", data);
	old = grep("OLDPWD", data);
	free(old->value);
	old->value = ft_strdup(pwd->value);
	free(old->line);
	old->line = var_join("OLDPWD", pwd->value);
}

void    cd(char *path, t_data *data)
{
	update_oldpwd(data);
	if (!path)
		go_home(data);
	else if (ft_strncmp(path, "../", 4) == 0 || ft_strncmp(path, "..", 3) == 0)
		go_back(data);
	// else if (ft_strncmp(path, "../", 4) > 0)
	
	// else if (ft_strncmp(path, "./", 3) == 0 || ft_strncmp(path, ".", 2) == 0)
	// 	return ;
	else
		data->status = chdir(path) * -1;
	data->newenv = true;
}
