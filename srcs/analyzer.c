/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:42:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/08 19:49:25 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	display_n_free(t_token *token_list)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
			printf("%zu WORD: |%s|\n", tmp->index, tmp->data);
		else if (tmp->type == PIPE)
			printf("%zu PIPE: |%s|\n", tmp->index, tmp->data);
		else if (tmp->type == LESS)
			printf("%zu LESS: |%s|\n", tmp->index, tmp->data);
		else if (tmp->type == GREAT)
			printf("%zu GREAT: |%s|\n", tmp->index, tmp->data);
		else if (tmp->type == DLESS)
			printf("%zu DLESS: |%s|\n", tmp->index, tmp->data);
		else if (tmp->type == DGREAT)
			printf("%zu DGREAT: |%s|\n", tmp->index, tmp->data);
		else if (tmp->type == END)
			printf("%zu END.\n", tmp->index);
		tmp = tmp->next;
	}
	free_toklist(token_list);
}
