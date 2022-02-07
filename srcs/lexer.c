/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:48:39 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/07 14:56:53 by chduong          ###   ########.fr       */
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

static void	add_token(t_token **list, t_token *token)
{
	t_token	*tmp;

	if (*list == NULL)
	{
		printf("Creating list.\n");
		*list = token;
		(*list)->previous = NULL;
	}
	else
	{
		printf("Adding token.\n");
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
		token->previous = tmp;
	}
}

t_bool	create_token(t_token_type type, char *data, t_token **list)
{
	t_token	*token;

	if ((data == NULL || data[0] == '\0') && (type != NONE && type != END))
		return (false);
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("malloc");
		return (false);
	}
	token->type = type;
	token->data = data;
	token->next = NULL;
	add_token(list, token);
	return (true);
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

t_token	*lexer(char *input)
{
	char	*str;
	t_token	*token_list;

	if (!input)
		return (NULL);
	str = cleaner(input);
	if (str == NULL)
	{
		ft_putstr_fd("Error: Corrupted Input\n", 2);
		return (NULL);
	}
	token_list = NULL;
	token_list = scanner(str);
	free(str);
	if (token_list == NULL)
	{
		ft_putstr_fd("Error: Tokenizer Failed\n", 2);
		return (NULL);
	}
	return (token_list);
}
