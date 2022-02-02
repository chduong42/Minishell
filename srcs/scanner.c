/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:31:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/02 19:24:43 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	is_in_charset(char c, char *charset)
{
	int		i;

	if (!charset || c == '\0')
		return (FALSE);
	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (TRUE);
		++i;
	}
	return (FALSE);
}

int	free_toklist(t_token *list)
{
	t_token	*tmp;

	if (list != NULL)
	{
		while (list)
		{
			tmp = list;
			if (list->next != NULL)
				list = list->next;
			if (tmp->type == WORD)
				free(tmp->data);
			free(tmp);
			tmp = NULL;
		}
	}
	return (-1);
}

t_token	*scanner(const char *str)
{
	t_token		*token_list;
	size_t		i;

	if (!str)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (str[i])
	{
		if (categorizer(str, token_list, &i) == FALSE)
			break ;
	}
	if (create_token(END, NULL, token_list) == FALSE)
		return (free_toklist(token_list));
	return (token_list);
}
