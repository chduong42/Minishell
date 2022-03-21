/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:04:58 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/21 11:51:12 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
static bool	quoted(t_token *tmp)
{
	if (tmp->type == WORD)
	{
		printf("Is [%s] quoted?", tmp->data);
		if (tmp->data[0] == '\''
			&& tmp->data[ft_strlen(tmp->data) - 1] == '\'')
			return (true);
		else if (tmp->data[0] == '\"'
			&& tmp->data[ft_strlen(tmp->data) - 1] == '\"')
			return (true);
	}
	printf("No it isn't.\n");
	return (false);
}
*/

bool	checker_words(t_token *token_list)
{
	t_token	*tmp;
	t_token	*tmp2;
	size_t	end_word;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			tmp2 = tmp;
			while (tmp2 != NULL)
			{
				if (tmp2->next == NULL || tmp2->next->type != WORD)
				{
					end_word = tmp2->index;
					break ;
				}
				tmp2 = tmp2->next;
			}
			if (reduce_words(tmp, end_word) == false)
				return (false);
//			tmp->data = cleaner(tmp->data);
		}
		tmp = tmp->next;
	}
	return (true);
}
