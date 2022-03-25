/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:47:56 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/25 13:00:26 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Reproduce the behavior of multiple pipes, adding file redirectors too.
*/
static void	redirection_handler(t_token *token_list, char **envp, t_data *data)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (pipe(tmp->pipefd) == -1)
			{
				perror("pipe failed.");
				exit_ms(NULL, data);
			}
			tmp->previous->out = tmp->pipefd[0];
			tmp->next->in = tmp->pipefd[1];
		}
		tmp = tmp->next;
	}
	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			
			fork_exec(tmp, envp, data);
		}
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
		redirection_handler(token_list, envp, data);
	if (token_list)
		free_toklist(token_list);
	return (true);
}
