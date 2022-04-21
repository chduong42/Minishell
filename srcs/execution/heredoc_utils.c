/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:28:15 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/21 19:01:38 by chduong          ###   ########.fr       */
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

static void	warning_eof(char *delim)
{
	if (g_status == 130)
		return ;
	ft_putstr_fd("MiniShell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

static char	*heredoc_prompt(char *delim)
{
	char	*line;
	char	*tmp;
	char	*buffer;

	buffer = ft_strdup("");
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, delim) == 0)
			break ;
		tmp = buffer;
		buffer = ft_strjoin(tmp, line);
		free(tmp);
		tmp = buffer;
		buffer = ft_strjoin(tmp, "\n");
		free(line);
		line = readline("> ");
	}
	if (line == NULL)
		warning_eof(delim);
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
