/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:42:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/11 15:45:38 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	type_display(t_token *tmp)
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
	else if (tmp->type == VAR)
		printf("%zu VAR: |%s|\n", tmp->index, tmp->data);
	else if (tmp->type == DQUOTE)
		printf("%zu DQUOTE: |%s|\n", tmp->index, tmp->data);
	else if (tmp->type == SQUOTE)
		printf("%zu SQUOTE: |%s|\n", tmp->index, tmp->data);
}

void	display_toklist(t_token *token_list)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type != END)
			type_display(tmp);
		else
			printf("%zu END.\n", tmp->index);
		tmp = tmp->next;
	}
}
