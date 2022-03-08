/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:15:08 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/08 14:37:49 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_valid_pipe(t_token *elem)
{
	if (elem->type == PIPE)
	{
		if (elem->previous == NULL || elem->previous->type != WORD)
			return (false);
		if (elem->next == NULL || elem->next->type != WORD)
			return (false);
		return (true);
	}
	return (false);
}

static bool	is_valid_less(t_token *elem)
{
	if (elem->type == LESS || elem->type == DLESS)
	{
		if (elem->previous != NULL && elem->previous->type != WORD)
			return (false);
		if (elem->next == NULL || elem->next->type != WORD)
			return (false);
		return (true);
	}
	return (false);
}

static bool	is_valid_great(t_token *elem)
{
	if (elem->type == GREAT || elem->type == DGREAT)
	{
		if (elem->previous != NULL && elem->previous->type != WORD)
			return (false);
		if (elem->next == NULL || elem->next->type != WORD)
			return (false);
		return (true);
	}
	return (false);
}

bool	checker_redir(t_token *token_list)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
		{
			if (is_valid_pipe(tmp) == false)
				return (false);
		}
		else if (tmp->type == LESS || tmp->type == DLESS)
		{
			if (is_valid_less(tmp) == false)
				return (false);
		}
		else if (tmp->type == GREAT || tmp->type == DGREAT)
		{
			if (is_valid_great(tmp) == false)
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
