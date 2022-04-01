/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:00:24 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/01 15:43:12 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Removes the first string from the string array "cmd" in token elem.
Returns this string, or NULL if any error occurs.
*/
char	*pop_first_cmd(t_token *elem, t_data *data)
{
	char	*str;
	char	**cmd_tmp;
	size_t	i;

	if (elem == NULL || elem->type != WORD || elem->cmd == NULL)
		return (NULL);
	str = ft_strdup(elem->cmd[0]);
	i = 0;
	while (elem->cmd[i] != NULL)
		++i;
	if (i <= 1)
		lst_pop(elem, &data->token_list);
	else
	{
		cmd_tmp = malloc(sizeof(char *) * i);
		if (cmd_tmp == NULL)
		{
			perror("MiniShell: malloc failed");
			free(str);
			return (NULL);
		}
		i = 0;
		while (elem->cmd[i] != NULL)
		{
			cmd_tmp[i] = elem->cmd[i + 1];
			++i;
		}
		free(elem->cmd);
		elem->cmd = cmd_tmp;
	}
	return (str);
}

char	*get_filepath(char **filename)
{
	char	*pwd;
	char	*filepath;

	if (*filename == NULL)
		return (NULL);
	if (*filename[0] == '/')
		return (*filename);
	pwd = getcwd(NULL, 0);
	filepath = path_join(pwd, *filename);
	free(pwd);
	pwd = NULL;
	free(*filename);
	*filename = NULL;
	return (filepath);
}
