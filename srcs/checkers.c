/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:53:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/17 17:38:14 by smagdela         ###   ########.fr       */
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
Trims every boundary space from each WORD token in the list,
starting from "elem".
*/
static void	trim_workspaces(t_token *elem)
{
	/*Code here MF*/
}

bool checker_quotes(t_token *token_list)
{
	t_token	*tmp;
	size_t	ends;
	size_t	endd;

	tmp = token_list;
	ends = 42;
	endd = 42;
	while (tmp != NULL)
	{
		if (tmp->type == SQUOTE)
		{
			ends = is_closed(tmp, SQUOTE);
			if (ends == 0 && endd == 0)
			{
				trim_wordspaces(tmp);
				break ;
			}
			else if (ends != 0)
				reduce_all(tmp, ends);
		}
		else if (tmp->type == DQUOTE)
		{
			endd = is_closed(tmp, SQUOTE);
			if (ends == 0 && endd == 0)
			{
				trim_wordspaces(tmp);
				break ;
			}
			else if (endd != 0)
				reduce(tmp, endd);
		}
		tmp = tmp->next;
	}
	/*
	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == SQUOTE || tmp->type == DQUOTE)
		{
			...
		}
		tmp = tmp->next;
	}

	Here should be everything regarding unclosed quotes,
	trimming of spaces, etc...
	
	*/
}
