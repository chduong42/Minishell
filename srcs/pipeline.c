/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:47:56 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/24 13:59:35 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Reproduce the behavior of multiple pipes, adding file redirectors too.
*/
static void	pipexator(t_token *token_list, char **envp, t_data *data)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipex(tmp->previous->cmd, tmp->next->cmd);
		tmp = tmp->next;
	}
}

/*
Launch the execution of the whole token_list, and frees it.
*/
bool	executor(t_token *token_list, char **envp, t_data *data)
{
	if (token_list == NULL)
		return (false);
	if (token_list->next == NULL)
		parse_line(token_list->cmd, envp, data);
	else
		pipexator(token_list, envp, data);
	free_toklist(token_list);
	return (true);
}
