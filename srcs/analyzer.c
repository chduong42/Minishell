/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:42:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/14 18:01:56 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	type_display(t_token *tmp)
{
	if (tmp->type == WORD)
		printf("%zu WORD: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == PIPE)
		printf("%zu PIPE: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == LESS)
		printf("%zu LESS: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == GREAT)
		printf("%zu GREAT: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == DLESS)
		printf("%zu DLESS: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == DGREAT)
		printf("%zu DGREAT: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == VAR)
		printf("%zu VAR: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == DQUOTE)
		printf("%zu DQUOTE: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == SQUOTE)
		printf("%zu SQUOTE: [%s]\n", tmp->index, tmp->data);
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
Displays an optional syntax error message "str", and delete token_list.
*/
static void	synerror(char *str, t_token **token_list)
{
	ft_putstr_fd("Minishell : Syntax Error", 2);
	if (str != NULL)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	if (*token_list != NULL)
	{
		free_toklist(*token_list);
		*token_list = NULL;
	}
}

t_token	*analyzer(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;

	checker_quotes(token_list, env_data);
	checker_words(token_list, env_data);
	if (checker_redir(token_list) == false)
	{
		synerror(" near redirection or pipe.", &token_list);
		return (token_list);
	}
	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == NONE || tmp->type == VAR || tmp->type == DQUOTE
			|| tmp->type == SQUOTE || ft_strlen(tmp->data) == 0)
		{
			synerror(" : Analyzer failure.", &token_list);
			break ;
		}
		tmp = tmp->next;
	}
	return (token_list);
}
