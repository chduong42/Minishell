/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:31:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/22 15:29:26 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Returns true if "c" is in "charset", false otherwise.
*/
bool	is_in_charset(char c, char *charset)
{
	int		i;

	if (!charset || c == '\0')
		return (false);
	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		++i;
	}
	return (false);
}

/*
Completely frees the token list, as well as data for each concerned token.
Returns -1 (for norm and ease of code reasons).
*/
int	free_toklist(t_token *list)
{
	t_token	*tmp;
	t_token	*to_free;

	if (list != NULL)
	{
		tmp = list;
		while (tmp)
		{
			if (tmp->type == WORD || tmp->type == VAR)
				free(tmp->data);
			if (tmp->cmd != NULL)
				free_tab(tmp->cmd);
			to_free = tmp;
			tmp = tmp->next;
			free(to_free);
			printf("Trying to free the %luth token, of data [%s]\n", tmp->index, tmp->data);
			to_free = NULL;
		}
	}
	return (-1);
}

/*
Core function of the lexer.
*/
t_token	*scanner(const char *str)
{
	t_token		*token_list;
	t_input		input;

	if (!str)
	{
		token_list = NULL;
		ft_putstr_fd("Error: Null string passed to scanner\n", 2);
		return (NULL);
	}
	token_list = NULL;
	input.str = str;
	input.index = 0;
	while (input.index < ft_strlen(str))
	{
		if (categorizer(&input, &token_list) == false)
			break ;
	}
	if (token_list == NULL)
		return (NULL);
	return (token_list);
}
