/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:31:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/07 14:56:53 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	is_in_charset(char c, char *charset)
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
	size_t		i;
	t_token		*token_list;

	if (!str)
	{
		token_list = NULL;
		ft_putstr_fd("Error: Null string passed to scanner\n", 2);
		return (NULL);
	}
	i = 0;
	token_list = NULL;
	while (i < ft_strlen(str))
	{
		if (categorizer(str, &token_list, &i) == false)
			break ;
	}
	if (token_list == NULL)
		return (NULL);
	if (create_token(END, NULL, &token_list) == false)
	{
		free_toklist(token_list);
		return (NULL);
	}
	return (token_list);
}
