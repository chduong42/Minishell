/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:42:02 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/21 16:23:53 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Displays an optional syntax error message "str", and delete token_list.
*/
static void	synerror(char *str, t_data *data)
{
	ft_putstr_fd("MiniShell: Syntax Error", 2);
	if (str != NULL)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	g_status = 2;
	if (data->token_list != NULL)
	{
		free_toklist(&data->token_list);
		data->token_list = NULL;
	}
}

static void	last_check(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp != NULL)
	{
		if (tmp->type == NONE || tmp->type == VAR || tmp->type == DQUOTE
			|| tmp->type == SQUOTE
			|| (data->token_list->next == NULL
				&& data->token_list->type != WORD))
		{
			synerror(NULL, data);
			break ;
		}
		tmp = tmp->next;
	}
}

void	analyzer(t_data *data)
{
	if (checker_quotes(data->token_list, data) == false)
	{
		synerror(": Near token quote.", data);
		return ;
	}
	expand_remaining_envar(data);
	suppress_spaces(&data->token_list);
	if (data->token_list == NULL)
	{
		synerror(": Bad input.", data);
		return ;
	}
	if (checker_words(data->token_list) == false)
	{
		synerror(": Near token word.", data);
		return ;
	}
	if (checker_redir(data->token_list) == false)
	{
		synerror(": Near redirection token.", data);
		return ;
	}
	last_check(data);
}
