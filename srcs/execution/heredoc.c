/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:40:24 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/05 18:23:30 by smagdela         ###   ########.fr       */
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

	envar_name = ft_substr(*str, i,
			find_char_set(*str + i, "\t\n\v\f\r$ "));
	envar_value = find_envar(envar_name, data);
	new_data = ft_substr(*str, 0, ft_strlen(envar_value));
	new_data = my_strcat(new_data, envar_value);
	new_data = my_strcat(new_data,
			ft_substr(*str, i + ft_strlen(envar_name),
				ft_strlen(*str) - i - ft_strlen(envar_name)));
	free(envar_name);
	free(envar_value);
	free(*str);
	*str = new_data;
	return (ft_strlen(envar_value) - 1);
}

/*
Expand environement variables inside the already expanded ones, if present.
*/
static void	matriochka(char **str, t_data *data)
{
	size_t	i;

	i = 0;
	while (*str[i])
	{
		if (*str[i] == '$'
			&& find_char_set(*str + i, "\t\n\v\f\r$ ") != 0)
		{
			i += matriochka_aux(str, data, i);
		}
		++i;
	}
}

static void	create_input_file(char *buffer, t_token **tmp)
{
	int		fd;

	fd = open("/tmp", O_TMPFILE | O_WRONLY | O_EXCL, 00700);
	printf("fd = %d\n", fd);
	if (write(fd , buffer, ft_strlen(buffer) < ft_strlen(buffer)))
	{
		perror("MiniShell: Error");
		close(fd);
		fd = -1;
	}
	free(buffer);
	if ((*tmp)->previous == NULL && (*tmp)->next)
	{
		if ((*tmp)->next->in != -1)
			close((*tmp)->next->in);
		(*tmp)->next->in = fd;
	}
	else if ((*tmp)->previous)
	{
		if ((*tmp)->previous->in != -1)
			close((*tmp)->previous->in);
		(*tmp)->previous->in = fd;
	}
	else
		close (fd);
}

void	heredoc(char *delim, t_token **tmp, t_data *data)
{
	char	*buffer;
	char	*line;
	char	*to_free;

	if (!delim || !*tmp)
		return (perror("MiniShell: Bad Heredoc"));
	buffer = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delim) == 0)
			break ;
		to_free = buffer;
		buffer = ft_strjoin(to_free, "\n");
		free(to_free);
		to_free = buffer;
		buffer = ft_strjoin(to_free, line);
		free(to_free);
		free(line);
	}
	free(line);
	if ((*tmp)->heredoc_expand == true)
		matriochka(&buffer, data);
	create_input_file(buffer, tmp);
}
