/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:04:58 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/18 19:04:43 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			reduce_words(tmp, end_word);
		}
	}
}
