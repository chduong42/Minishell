/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:31:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/11 16:59:32 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_in_charset(char c, char *charset)
{
	int		i;

	if (!charset || c == '\0')
		return (false);
	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		++i;
	}
	return (false);
}

int	free_toklist(t_token *list)
{
	t_token	*tmp;

	if (list != NULL)
	{
		tmp = list;
		while (tmp)
		{
			if (tmp->type == WORD || tmp->type == VAR)
				free(tmp->data);
			if (tmp->next != NULL)
			{
				tmp = tmp->next;
				free(tmp->previous);
				tmp->previous = NULL;
			}
			else
			{
				free(tmp);
				tmp = NULL;
			}
		}
	}
	return (-1);
}

static t_input	init_input(const char *str)
{
	t_input		input;

	input.str = str;
	input.index = 0;
	input.dquoted = false;
	input.squoted = false;
	return (input);
}

t_token	*scanner(const char *str)
{
	t_token		*token_list;
	t_input		input;

	if (!str)
	{
		token_list = NULL;
		ft_putstr_fd("Error: Null string passed to scanner\n", 2);
		return (NULL);
	}
	token_list = NULL;
	input = init_input((char *)str);
	while (input.index < ft_strlen(str))
	{
		if (categorizer(&input, &token_list) == false)
			break ;
	}
	if (token_list == NULL)
		return (NULL);
	if (create_token(END, NULL, &token_list) == false)
	{
		free_toklist(token_list);
		return (NULL);
	}
	return (token_list);
}
