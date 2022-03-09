/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:42:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/09 15:06:11 by smagdela         ###   ########.fr       */
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
		type_display(tmp);
		tmp = tmp->next;
	}
}

/*
Displays a syntax error message "str", and frees the "token_list".
*/
static void	synerror(t_token *token_list, char *str)
{
	free_toklist(token_list);
	token_list = NULL;
	ft_putstr_fd("Minishell : Syntax Error : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	analyzer(t_token *token_list, t_data *env_data)
{
	printf("\nChecking quotes...\n");
	checker_quotes(token_list, env_data);
	display_toklist(token_list);
	printf("Quotes OK!\n\nChecking words...\n");
	checker_words(token_list);
	display_toklist(token_list);
	printf("Words OK!\n\nChecking redir...\n");
	if (checker_redir(token_list) == false)
		synerror(token_list, "Near redirection or pipe.");
	printf("Redir OK!\nEnd of parser.\n\n");
}
