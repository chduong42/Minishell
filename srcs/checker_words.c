/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:04:58 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/14 13:36:32 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	expand_remaining_envar(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == VAR)
			expand(tmp, env_data);
		tmp = tmp->next;
	}
}

void	checker_words(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;
	t_token	*tmp2;
	size_t	end_word;

	expand_remaining_envar(token_list, env_data);
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
		tmp = tmp->next;
	}
}
