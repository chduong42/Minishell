/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:48:39 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/02 19:41:30 by smagdela         ###   ########.fr       */
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

t_bool	create_token(t_token_type type, char *data, t_token *list)
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

/*
Will return position of the next char from charset.
Returns 0 otherwise.
*/
size_t	find_char_set(const char *str, char *charset)
{
	size_t	i;
	size_t	j;

	if (!str || !charset)
		return (0);
	i = 1;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j])
				return (i);
			j++;
		}
		++i;
	}
	return (0);
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
