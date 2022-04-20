/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:28:15 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/20 17:57:04 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	heredoc_expand_exception(t_token *elem)
{
	t_token	*tmp;

	if (elem == NULL)
		return (false);
	tmp = elem->previous;
	while (tmp)
	{
		if (tmp->type == DLESS)
			return (true);
		else if (is_legit(tmp) == false)
			tmp = tmp->previous;
		else
			return (false);
	}
	return (false);
}

static char	*heredoc_prompt(char *delim)
{
	char	*line;
	char	*buffer;
	char	*to_free;

	buffer = ft_strdup("");
	line = readline("> ");
	while (line)
	{
		to_free = buffer;
		if (ft_strcmp(buffer, ""))
		{
			buffer = ft_strjoin(to_free, "\n");
			free(to_free);
		}
		if (ft_strcmp(line, delim) == 0)
			break ;
		to_free = buffer;
		buffer = ft_strjoin(to_free, line);
		free(to_free);
		free(line);
		line = readline("> ");
	}
	free(line);
	return (buffer);
}

void	child_prompt(char *delim, t_token **tmp, t_data *data)
{
	char	*buffer;

	close((*tmp)->pipefd[0]);
	buffer = heredoc_prompt(delim);
	if ((*tmp)->heredoc_expand == true)
		matriochka(&buffer, data);
	ft_putstr_fd(buffer, (*tmp)->pipefd[1]);
	close((*tmp)->pipefd[1]);
	free(buffer);
	free_exit(data, EXIT_SUCCESS);
}
