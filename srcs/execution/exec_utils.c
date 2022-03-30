/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:50:54 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/30 18:46:16 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_binpath(char *filename, t_data *data)
{
	char	*pwd;
	char	*filepath;
	size_t	i;

	if (filename == NULL)
		return (NULL);
	if (filename[0] == '/')
		filepath = ft_strdup(filename);
	else if (filename[0] == '.')
	{
		pwd = getcwd(NULL, 0);
		filepath = path_join(pwd, filename);
		free(pwd);
	}
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
