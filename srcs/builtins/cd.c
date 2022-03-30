/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:51:15 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/30 20:30:43 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_home(t_data *data)
{
	char 	*tmp;
	t_list	*pwd_env;
	
	tmp = getenv("HOME");
	if (tmp)
		data->status = chdir(tmp) * -1;
	else
	{
		printf("Minishell: cd: HOME not set\n");
		data->status = 1;
	}
	if (data->status == 0)
	{
		pwd_env = grep("PWD", data);
		free(pwd_env->value)
		pwd_env->value = ft_strdup(tmp);
		free(pwd_env->line);
		pwd_env->line = var_join("PWD", pwd_env->value);
	}
}

void	go_back(t_data *data)
{
	int		i;
	char	*pwd;
	char	*tmp;
	
	pwd = getcwd(NULL, 0);
	i = 0;
	while (pwd[i])
		++i;
	while (pwd[i] != '/')
		--i;
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, pwd, i + 1);
	data->status = chdir(tmp) * -1;
	if (data->status == 0)
		
	free(pwd);
	free(tmp);
}

void	old_pwd(char *old_value, t_data *data)
{
	t_list	*old;
	
	old = grep("OLDPWD", data);
	free(old->line);
	free(old->value);
	old->value = old_value;
}

void    cd(char *path, t_data *data)
{
	if (!path)
		go_home(data);
	else if (ft_strncmp(path, "../", 4) == 0 || ft_strncmp(path, "..", 3) == 0)
		go_back(data)
	// else if (ft_strncmp(path, "../", 4) > 0)
	
	// else if (ft_strncmp(path, "./", 3) == 0 || ft_strncmp(path, ".", 2) == 0)
	// 	return ;
	// else
	// 	chdir(path);
}
