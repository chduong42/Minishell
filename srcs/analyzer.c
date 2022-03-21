/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:42:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/21 12:12:48 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("[%s] ", tab[i]);
		++i;
	}
	printf("\n");
}

static void	type_display(t_token *tmp)
{
	if (tmp->type == WORD && tmp->data != NULL)
		printf("%zu WORD (data) : [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == WORD && tmp->cmd != NULL)
	{
		printf("%zu WORD (cmd) : ", tmp->index);
		print_tab(tmp->cmd);
	}
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

t_token	*analyzer(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;

	checker_quotes(token_list, env_data);
	expand_remaining_envar(token_list, env_data);
	if (checker_words(token_list) == false)
	{
		synerror(" : Near token word.", &token_list);
		return (token_list);
	}
	if (checker_redir(token_list) == false || token_list == NULL
		|| (token_list->next == NULL && token_list->type != WORD))
	{
		synerror(" : Near redirection token.", &token_list);
		return (token_list);
	}
	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == NONE || tmp->type == VAR || tmp->type == DQUOTE
			|| tmp->type == SQUOTE)
		{
			synerror(" : Analyzer failure.", &token_list);
			break ;
		}
		tmp = tmp->next;
	}
	return (token_list);
}
