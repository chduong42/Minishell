/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:50:54 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/31 12:02:57 by smagdela         ###   ########.fr       */
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
			free(filepath);
			filepath = NULL;
			++i;
		}
	}
	return (filepath);
}

char	*path_join(char *path, char *cmd)
{
	char	*p;
	int		len1;
	int		len2;

	if (!path || !cmd)
		return (NULL);
	len1 = ft_strlen(path);
	len2 = ft_strlen(cmd);
	p = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!p)
		return (NULL);
	ft_strlcpy(p, path, len1 + 1);
	ft_strlcat(p, "/", len1 + 2);
	ft_strlcat(p, cmd, len1 + len2 + 2);
	return (p);
}
