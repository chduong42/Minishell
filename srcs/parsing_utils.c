/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:26:15 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/18 18:47:50 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Takes 2 strings and return only one newly malloc'dstring,
concatenation of the two arguments.
WARNING: Frees the first argument!
*/
char	*my_strcat(char *dest, char *str)
{
	size_t	len1;
	size_t	len2;
	char	*tmp;
	size_t	i;

	len1 = ft_strlen(dest);
	len2 = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (tmp == NULL)
		return (NULL);
	if (dest != NULL && len1 != 0)
	{
		i = 0;
		while (dest[i])
		{
			tmp[i] = dest[i];
			++i;
		}
		free(dest);
	}
	ft_strlcpy(tmp + len1, str, len2 + 1);
	return (tmp);
}

/*
Finds "envar" in "envp" and returns its value,
according to the environmenet format.
If no envar with such a name exists, returns an empty string "".
Even if empty, the string is malloc'd, so that double frees won't happen.
Treats special envar like $?.
*/
char	*find_envar(char *envar, char **envp)
{
	/*
	char	*ret;

	ret = malloc();
	
	etc...
	*/
}

void	lst_pop(t_token *elem)
{
	t_token	*tmp;

	if (elem == NULL)
		return ;
	if (elem->type == WORD || elem->type == VAR)
		free(elem->data);
	if (elem->previous == NULL && elem->next == NULL)
	{
	}
	else
	{
		elem->next->previous = elem->previous;
		elem->previous->next = elem->next;
		tmp = elem->next;
		while (tmp != NULL)
		{
			if (tmp->previous == NULL)
				tmp->index = 0;
			else
				tmp->index = tmp->previous->index + 1;
			tmp = tmp->next;
		}
	}
	free(elem);
	elem = NULL;
}
