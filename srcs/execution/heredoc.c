/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:40:24 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/07 16:31:29 by smagdela         ###   ########.fr       */
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

static size_t	matriochka_aux(char **str, t_data *data, size_t i)
{
	char	*envar_name;
	char	*envar_value;
	char	*new_data;
	size_t	len;

	envar_name = ft_substr(*str, i + 1, ft_envarlen(*str + i + 1));
	envar_value = find_envar(envar_name, data);
	new_data = ft_substr(*str, 0, i);
	new_data = my_strcat(new_data, envar_value);
	new_data = my_strcat(new_data, *str + i + ft_strlen(envar_name) + 1);
	free(envar_name);
	len = ft_strlen(envar_value);
	free(envar_value);
	free(*str);
	*str = new_data;
	return (len - 1);
}

/*
Expand environement variables inside the already expanded ones, if present.
*/
static void	matriochka(char **str, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(*str) && (*str)[i])
	{
		if ((*str)[i] == '$')
		{
			i += matriochka_aux(str, data, i);
		}
		++i;
	}
}

static void	child_prompt(char *delim, t_token **tmp, t_data *data)
{
	char	*buffer;
	char	*line;
	char	*to_free;

	close((*tmp)->pipefd[0]);
	buffer = ft_strdup("");
	while (1)
	{
		line = readline("> ");
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
	}
	free(line);
	if ((*tmp)->heredoc_expand == true)
		matriochka(&buffer, data);
	ft_putstr_fd(buffer, (*tmp)->pipefd[1]);
	close((*tmp)->pipefd[1]);
	free(buffer);
	free_exit(data, EXIT_SUCCESS);
}

void	heredoc(char *delim, t_token **tmp, t_data *data)
{
	pid_t	pid;

	if (!delim || !*tmp)
		return (perror("MiniShell: Bad Heredoc"));
	if (pipe((*tmp)->pipefd) == -1)
		return (perror("MiniShell: Pipe failed"));
	else
	{
		if ((*tmp)->previous)
		{
			if ((*tmp)->previous->in != -1)
				close((*tmp)->previous->in);
			(*tmp)->previous->in = (*tmp)->pipefd[0];
		}
		else if ((*tmp)->next)
		{
			if ((*tmp)->next->in != -1)
				close((*tmp)->next->in);
			(*tmp)->next->in = (*tmp)->pipefd[0];
		}
	}
	pid = fork();
	if (pid < 0)
		return (perror("MiniShell: Error"));
	else if (pid == 0)
		child_prompt(delim, tmp, data);
	close((*tmp)->pipefd[1]);
	waitpid(pid, NULL, 0);
}
