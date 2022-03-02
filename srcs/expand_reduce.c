/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_reduce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:19:43 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/02 19:13:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Replace current VAR token with the expanded WORD version of it,
if the VAR is found in the environement.
*/
void	expand(t_token *elem, t_data *env_data)
{
	size_t	i;

	if (elem->type != VAR)
		return ;
	elem->type = WORD;
	elem->data = find_envar(elem->data, env_data);
	i = 0;
	while (elem->data[i])
	{
		if (elem->data[i] == '$'
			&& (ft_isalnum(elem->data[i])
				|| is_in_charset(elem->data[i], "_?")))
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
and frees accordingly (links "elem" to "tmp").

			  Redirect...
	/-->-->-->-->-->-->-->-->-->-->-->-->\
   |									  |
elem-> | elem+1->elem+2->...->tmp-1-> | tmp->tmp+1->...

		  ^...then frees this part.^

Refreshes to the new indexes too.
*/
static void	relink_toklist(t_token *elem, t_token *tmp, char *new_data)
{
	t_token	*to_free;

	elem->data = new_data;
	elem->type = WORD;
	to_free = elem->next;
	elem->next = tmp;
	if (tmp != NULL)
	{	
		tmp->previous->next = NULL;
		tmp->previous = elem;
	}
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
	t_token	*elem_end;
	char	*new_data;

	tmp = elem->next;
	if (tmp == NULL)
		return ;
	new_data = "";
	while (tmp != NULL && tmp->index < end)
	{
		new_data = my_strcat(new_data, tmp->data);
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		free(new_data);
		return ;
	}
	elem_end = tmp->next;
	lst_pop(tmp);
	relink_toklist(elem, tmp->next, new_data);
}

/*
Reduce everything between "elem" and the elem with index "end" from toklist.
Meaning everything (BUT NOT environement variables) will become one and
only one token of type WORD, AFTER EXPANDING ENVIRONMENT VARIABLES,
without the quotes on each sides.
To use with double quotes.
*/
void	reduce(t_token *elem, size_t end, t_data *env_data)
{
	t_token	*tmp;
	t_token	*elem_end;
	char	*new_data;

	tmp = elem->next;
	if (tmp == NULL)
		return ;
	new_data = "";
	while (tmp != NULL && tmp->index < end)
	{
		if (tmp->type == VAR)
			expand(tmp, env_data);
		new_data = my_strcat(new_data, tmp->data);
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		free(new_data);
		return ;
	}
	elem_end = tmp->next;
	lst_pop(tmp);
	relink_toklist(elem, elem_end, new_data);
}

/*
Reduce everything between "elem" and the elem with index "end" from toklist.
Meaning everything (including environment variables) will become one and
only one token of type WORD, including data from "elem" and "end"th token.
To use with checker_words.
*/
void	reduce_words(t_token *elem, size_t end)
{
	t_token	*tmp;
	char	*new_data;

	tmp = elem;
	if (tmp == NULL)
		return ;
	new_data = "";
	while (tmp != NULL && tmp->index < end)
	{
		new_data = my_strcat(new_data, tmp->data);
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		free(new_data);
		return ;
	}
	relink_toklist(elem, tmp, new_data);
}
