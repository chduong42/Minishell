/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:42:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/15 11:20:25 by smagdela         ###   ########.fr       */
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

/*
Temporary function used to display the tokenlist ,
in order to check tokenizer's good behavior.
Erase it before defense, as it contains forbidden functions.
*/
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

static t_token	*synerror(t_token *token_list, const char *str)
{
	free_toklist(token_list);
	ft_putstr_fd("Syntax Error : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

t_token	*analyzer(t_token *token_list)
{
	if (check_quotes(token_list) == false)
		return (synerror(token_list, "Near quotes."));
	if (check_envar(token_list) == false)
		return (synerror(token_list, "Near environment variable."));
	if (check_words(token_list) == false)
		return (synerror(token_list, "Near arg."));
	if (check_redir(token_list) == false)
		return (synerror(token_list, "Near redirection or pipe."));
	return (token_list);
}
