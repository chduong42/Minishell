/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:53:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/15 11:37:45 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Finds the next "elem_type" element in toklist,
and returns its index in the list;
If there are none, returns 0;
*/
static size_t	is_closed(t_token *elem, t_token_type elem_type)
{
	t_token	*tmp;

	if (elem == NULL)
		return (0);
	tmp = elem->next;
	while (tmp != NULL)
	{
		if (tmp->type == elem_type)
			return (tmp->index);
		tmp = tmp->next;
	}
	return (0);
}

/*
Reduce everything between "elem" and the elem with index "end" from toklist.
Meaning everything (including environement variables) will become one and
only one token of type WORD, without the quotes on each sides.
To use with single quotes.
*/
t_token	*reduce_all(t_token *elem, size_t end)
{
	
}

/*
Reduce everything between "elem" and the elem with index "end" from toklist.
Meaning everything (BUT NOT environement variables) will become one and
only one token of type WORD, without the quotes on each sides.
To use with double quotes.
*/
t_token	*reduce(t_token *elem, size_t end)
{
	
}

bool checker_quotes(t_token *token_list)
{
	t_token	*tmp;
	size_t	end;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == SQUOTE)
		{
			end = is_closed(tmp, SQUOTE);
			if (end != 0)
				reduce_all(tmp, end);
		}
		else if (tmp->type == DQUOTE)
		{
			end = is_closed(tmp, SQUOTE);
			if (end != 0)
				reduce(tmp, end);
		}
		tmp = tmp->next;
	}
}