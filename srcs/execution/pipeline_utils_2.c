/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:37:46 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/19 13:26:41 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_data *data)
{
	int		count;
	t_token	*tmp;

	count = 0;
	if (data == NULL || data->token_list == NULL)
		return (0);
	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->cmd != NULL)
			++count;
		tmp = tmp->next;
	}
	return (count);
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

void	close_pipes(pid_t pid, t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->pid == pid
			&& tmp->previous && tmp->previous->type == PIPE)
		{
			close(tmp->previous->pipefd[0]);
		}
		if (tmp->type == WORD && tmp->pid == pid
			&& tmp->next && tmp->next->type == PIPE)
		{
			close(tmp->next->pipefd[1]);
		}
		tmp = tmp->next;
	}
}
