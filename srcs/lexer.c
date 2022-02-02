/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:48:39 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/02 13:26:59 by smagdela         ###   ########.fr       */
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

static t_bool	*create_token(t_token_type type, char *data, t_token *list)
{
	t_token	*token;
	t_token	*tmp;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		perror("malloc");
		return (FALSE);
	}
	token->type = type;
	token->data = data;
	token->next = NULL;
	if (!list)
	{
		token->previous = NULL;
		list = token;
		return (TRUE);
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
		token->previous = tmp;
	}
	return (TRUE);
}

static t_token	*scanner(const char *str)
{
	size_t		i;
	t_token		*token_list;

	if (!str)
		return (NULL);
	i = 0;
	token_list = NULL;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<')
		{
			if (create_token(DLESS, "<<", token_list) == FALSE)
			{
				free_list(token_list);
				return (NULL);
			}
			i += 2;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{}
		else if (str[i] == '>' && str[i + 1] != '>')
		{}
		else if (str[i] == '>' && str[i + 1] == '>')
		{}
		else if (str[i] == '|')
		{}
		else if (str[i] == '"' && closing_quote(str[i], '"') == TRUE)
		{}
		else if (str[i] == 39 && closing_quote(str[i], 39) == TRUE)
		{}
		else
			++i;
	}
}

t_bool	lexer(char *input)
{
	char	*str;
	t_token	*token_list;

	if (!input)
		return (FALSE);
	str = cleaner(input);
	if (!str)
	{
		ft_putstr_fd("Error: Corrupted Input\n", 2);
		return (FALSE);
	}
	token_list = scanner(str);
	if (!token_list)
	{
		ft_putstr_fd("Error: Tokenizer Failed\n", 2);
		return (FALSE);
	}
}
