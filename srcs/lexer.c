/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:48:39 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/02 16:00:23 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*cleaner(char *str_in)
{
	char	*tmp;
	char	*str_out;

	if (!str_in)
		return (NULL);
	tmp = str_in;
	str_out = ft_strtrim(tmp, " \t\n\r\v\f");
	free(str_in);
	return (str_out);
}

static void	add_token(t_token *list, t_token *token)
{
	t_token	*tmp;

	if (!list)
	{
		token->previous = NULL;
		list = token;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
		token->previous = tmp;
	}
}

static t_bool	*create_token(t_token_type type, char *data, t_token *list)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		perror("malloc");
		return (FALSE);
	}
	token->type = type;
	token->data = data;
	token->next = NULL;
	add_token(list, token);
	return (TRUE);
}

static size_t	closing_quote(char *str, char quote)
{
	size_t	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		++i;
	}
	return (0);
}

static void	*free_list(t_token *list)
{
	t_token	*tmp;

	if (list == NULL)
		return (NULL);
	while (list)
	{
		tmp = list;
		if (list->next != NULL)
			list = list->next;
		if (tmp->type == WORD)
			free(tmp->data);
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

static t_token	*scanner(const char *str)
{
	size_t		i;
	t_token		*token_list;
	char		*word_data;

	if (!str)
		return (NULL);
	i = 0;
	token_list = NULL;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "<<", 2))
		{
			if (create_token(DLESS, "<<", token_list) == FALSE)
				return (free_list(token_list));
			i += 2;
		}
		else if (!ft_strncmp(str[i], "<", 2))
		{
			if (create_token(LESS, "<", token_list) == FALSE)
				return (free_list(token_list));
			++i;
		}
		else if (!ft_strncmp(str[i], ">>", 2))
		{
			if (create_token(DGREAT, ">>", token_list) == FALSE)
				return (free_list(token_list));
			i += 2;
		}
		else if (!ft_strncmp(str[i], ">", 2))
		{
			if (create_token(GREAT, ">", token_list) == FALSE)
				return (free_list(token_list));
			++i;
		}
		else if (!ft_strncmp(str[i], "|", 2))
		{
			if (create_token(PIPE, "|", token_list) == FALSE)
				return (free_list(token_list));
			++i;
		}
		else if (!ft_strncmp(str[i], "\"", 2) && closing_quote(str[i], '"'))
		{
			word_data = ft_substr(str, i, closing_quote(str[i], '"'));
			if (create_token(DQUOTE, word_data, token_list) == FALSE)
				return (free_list(token_list));
			i += ft_strlen(word_data);
		}
		else if (!ft_strncmp(str[i], "\"", 2) && !closing_quote(str[i], '"'))
		{
			if (create_token(WORD, word_data, token_list) == FALSE)
				return (free_list(token_list));
			i += ft_strlen(word_data);
		}
		else if (!ft_strncmp(str[i], "\'", 2) && closing_quote(str[i], 39))
		{
			if (create_token(SQUOTE, "\'", token_list) == FALSE)
				return (free_list(token_list));
			i += closing_quote(str[i], 39) + 1;
		}
		else if (!ft_strncmp(str[i], "\'", 2) && !closing_quote(str[i], 39))
		{
			if (create_token(WORD, word_data, token_list) == FALSE)
				return (free_list(token_list));
			i += ft_strlen(word_data);
		}
		else
			++i;
	}
	if (create_token(END, NULL, token_list) == FALSE)
		return (free_list(token_list));
	return (token_list);
}

t_bool	lexer(char *input, t_token *token_list)
{
	char	*str;

	if (!input)
		return (FALSE);
	str = cleaner(input);
	if (!str)
	{
		ft_putstr_fd("Error: Corrupted Input\n", 2);
		return (FALSE);
	}
	token_list = scanner(str);
	free(str);
	if (!token_list)
	{
		ft_putstr_fd("Error: Tokenizer Failed\n", 2);
		return (FALSE);
	}
	return (TRUE);
}
