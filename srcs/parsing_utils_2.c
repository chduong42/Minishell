/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:46:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/23 12:27:33 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Completely frees the token list, as well as data for each concerned token.
Returns -1 (for norm and ease of code reasons).
*/
int	free_toklist(t_token *list)
{
	t_token	*tmp;
	t_token	*to_free;

	if (list != NULL)
	{
		tmp = list;
		while (tmp)
		{
			if (tmp->type == WORD || tmp->type == VAR)
				free(tmp->data);
			if (tmp->cmd != NULL)
				free_tab(tmp->cmd);
			to_free = tmp;
			tmp = tmp->next;
			free(to_free);
			to_free = NULL;
		}
	}
	return (-1);
}

bool	ft_is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (true);
		++i;
	}
	return (false);
}

static void	glue_together(t_token **tmp, t_token **token_list)
{
	if ((*tmp)->previous && (*tmp)->previous->type == WORD
		&& ft_strncmp((*tmp)->previous->data, " ",
			ft_strlen((*tmp)->previous->data)))
	{
		*tmp = (*tmp)->previous;
		(*tmp)->data = my_strcat((*tmp)->data, (*tmp)->next->data);
		lst_pop((*tmp)->next, token_list);
	}
	if ((*tmp)->next && (*tmp)->next->type == WORD
		&& ft_strncmp((*tmp)->next->data, " ",
			ft_strlen((*tmp)->next->data)))
	{
		(*tmp)->data = my_strcat((*tmp)->data, (*tmp)->next->data);
		lst_pop((*tmp)->next, token_list);
	}
}

void	expand_remaining_envar(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == VAR)
		{
			expand(tmp, env_data);
			glue_together(&tmp, &token_list);
		}
		tmp = tmp->next;
	}
}
