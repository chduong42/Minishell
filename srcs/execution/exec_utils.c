/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:50:54 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/01 12:16:00 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_binpath_aux(char *filename)
{
	char	*pwd;
	char	*filepath;

	filepath = NULL;
	if (filename == NULL)
		return (NULL);
	else if (filename[0] == '/')
		return (ft_strdup(filename));
	else if (filename[0] == '.')
	{
		pwd = getcwd(NULL, 0);
		filepath = path_join(pwd, filename);
		free(pwd);
	}
	return (filepath);
}

char	*get_binpath(char *filename, t_data *data)
{
	char	*filepath;
	size_t	i;

	if (filename == NULL || filename[0] == '/' || filename[0] == '.')
		return (get_binpath_aux(filename));
	else
	{
		i = 0;
		while (data->path[i])
		{
			filepath = path_join(data->path[i], filename);
			if (access(filepath, X_OK) == 0)
				break ;
			if (data->path[i + 1])
				free(filepath);
			++i;
		}
	}
	return (filepath);
}
