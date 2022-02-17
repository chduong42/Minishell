/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_reduce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:19:43 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/17 17:24:58 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Replace current VAR token with the expanded WORD version of it,
if the VAR is found in the environement.
*/
void	expand(t_token *elem)
{
	size_t	i;

	if (elem->type != VAR)
		return ;
	elem->type = WORD;
	elem->data = find_envar(elem->data, envp);
	i = 0;
	while (elem->data[i])
	{
		if (elem->data[i] == '$'
			&& (ft_isalnum(elem->data[i]) || is_in_charset(elem->data[i], "_?")))
		{
			/*
			Treats the case when there are other envar
			to expand inside the already expanded ones.
			*/
		}
		++i;
	}
}

/*
Used to replace the previous sample of toklist with one token only,
and frees accordingly.
Refreshes to the new indexes too.
*/
static void	relink_toklist(t_token *elem, t_token *tmp, char *new_data)
{
	t_token	*to_free;

	elem->data = new_data;
	elem->type = WORD;
	to_free = elem->next;
	elem->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->previous = elem;
	tmp->next = NULL;
	to_free->previous = NULL;
	free_toklist(to_free);
	tmp = elem;
	while (tmp != NULL)
	{
		if (tmp->previous == NULL)
			tmp->index = 0;
		else
			tmp->index = tmp->previous->index + 1;
		tmp = tmp->next;
	}
}

/*
Reduce everything between "elem" and the elem with index "end" from toklist.
Meaning everything (including environment variables) will become one and
only one token of type WORD, without the quotes on each sides.
To use with single quotes.
*/
void	reduce_all(t_token *elem, size_t end)
{
	t_token	*tmp;
	char	*new_data;

	tmp = elem->next;
	if (tmp == NULL)
		return ;
	new_data = "";
	while (tmp->index < end)
	{
		if (tmp == NULL)
		{
			free(new_data);
			return ;
		}
		new_data = my_strcat(new_data, tmp->data);
		tmp = tmp->next;
	}
	relink_toklist(elem, tmp, new_data);
}

/*
Reduce everything between "elem" and the elem with index "end" from toklist.
Meaning everything (BUT NOT environement variables) will become one and
only one token of type WORD, AFTER EXPANDING ENVIRONMENT VARIABLES,
without the quotes on each sides.
To use with double quotes.
*/
void	reduce(t_token *elem, size_t end)
{
	t_token	*tmp;
	char	*new_data;

	tmp = elem->next;
	if (tmp == NULL)
		return ;
	new_data = "";
	while (tmp->index < end)
	{
		if (tmp == NULL)
		{
			free(new_data);
			return ;
		}
		else if (tmp->type == VAR)
			expand(tmp);
		new_data = my_strcat(new_data, tmp->data);
		tmp = tmp->next;
	}
	relink_toklist(elem, tmp, new_data);
}