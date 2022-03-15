/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:04:58 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/15 15:07:17 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	quoted(t_token *tmp)
{
	if (tmp->type == WORD)
	{
		if (tmp->data[0] == '\''
			&& tmp->data[ft_strlen(tmp->data) - 1] == '\'')
			return (true);
		else if (tmp->data[0] == '\"'
			&& tmp->data[ft_strlen(tmp->data) - 1] == '\"')
			return (true);
	}
	return (false);
}

void	checker_words(t_token *token_list)
{
	t_token	*tmp;
	t_token	*tmp2;
	char	*str;
	size_t	end_word;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			tmp2 = tmp;
			while (tmp2 != NULL)
			{
				if (quoted(tmp2) == true)
				{
					str = ft_strtrim(tmp2->data, "\"\'");
					free(tmp2->data);
					tmp2->data = str;
				}
				if (tmp2->next == NULL || tmp2->next->type != WORD)
				{
					end_word = tmp2->index;
					break ;
				}
				tmp2 = tmp2->next;
			}
			reduce_words(tmp, end_word);
			tmp->data = cleaner(tmp->data);
		}
		tmp = tmp->next;
	}
}
