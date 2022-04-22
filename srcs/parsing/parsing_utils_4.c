/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:10:45 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/22 12:22:30 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	glue_to_prev(t_token **tmp, t_token **token_list)
{
	if (is_legit((*tmp)->previous) == true && (*tmp)->previous
		&& (*tmp)->previous->type == WORD)
	{
		*tmp = (*tmp)->previous;
		(*tmp)->data = my_strcat((*tmp)->data, (*tmp)->next->data);
		lst_pop((*tmp)->next, token_list);
	}
}

void	glue_to_next(t_token **tmp, t_token **token_list)
{
	if (is_legit((*tmp)->next) == true && (*tmp)->next
		&& (*tmp)->next->type == WORD)
	{
		(*tmp)->data = my_strcat((*tmp)->data, (*tmp)->next->data);
		lst_pop((*tmp)->next, token_list);
	}
}

/*
Splits the result of the "elem" envar expansion into a new list of
WORD tokens, on each space.
It then relinks this new little list of tokens inside the
"token_list", where "elem" once was.
It does it only when there are no redirection before itself.
*/
t_token	*envar_split(t_token **elem)
{
	t_token	*tmp;
	char	**tab;
	t_token	*tmp_list;
	int		i;

	tmp = (*elem)->previous;
	while (tmp && is_legit(tmp) == false)
		tmp = tmp->previous;
	if (tmp && (is_redir_token(tmp) == true || (*elem)->data == NULL))
		return (*elem);
	else
	{
		tmp_list = NULL;
		tab = ft_split((*elem)->data, ' ');
		if ((*elem)->data[0] == ' ')
			create_token(WORD, ft_strdup(""), &tmp_list);
		i = 0;
		while (tab[i])
			create_token(WORD, ft_strdup(tab[i++]), &tmp_list);
		if (ft_strlen((*elem)->data) > 0
			&& (*elem)->data[ft_strlen((*elem)->data) - 1] == ' ')
			create_token(WORD, ft_strdup(""), &tmp_list);
		if ((*elem)->previous)
			(*elem)->previous->next = tmp_list;
		tmp_list->previous = (*elem)->previous;
		tmp = tmp_list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		if ((*elem)->next)
			(*elem)->next->previous = tmp;
		tmp->next = (*elem)->next;
		(*elem)->next = NULL;
		(*elem)->previous = NULL;
		free_toklist(elem);
		*elem = tmp_list;
		free_tab(tab);
		return (tmp);
	}
}
