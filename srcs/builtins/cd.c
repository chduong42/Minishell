/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:51:15 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/01 12:13:26 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
	t_list	*pwd_env;

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
}

void	update_oldpwd(t_data *data)
{
	t_list	*old;
	
	old = grep("OLDPWD", data);
	free(old->line);
	free(old->value);
	old->value = old_value;
	old->line = var_join("OLDPWD", old_value);
}

void    cd(char *path, t_data *data)
{
	update_oldpwd(data);
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
*/