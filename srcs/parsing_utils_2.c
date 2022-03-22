/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:46:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/22 17:30:24 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			to_free = NULL;
		}
	}
	return (-1);
}

bool	ft_is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (true);
		++i;
	}
	return (false);
}

void	expand_remaining_envar(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp != NULL)
	{
		if (tmp->type == VAR)
		{
			expand(tmp, env_data);
			if (tmp->previous && tmp->previous->type == WORD
				&& ft_strncmp(tmp->previous->data, " ",
					ft_strlen(tmp->previous->data)))
			{
				tmp = tmp->previous;
				tmp->data = my_strcat(tmp->data, tmp->next->data);
				lst_pop(tmp->next, &token_list);
			}
			if (tmp->next && tmp->next->type == WORD
				&& ft_strncmp(tmp->next->data, " ",
					ft_strlen(tmp->next->data)))
			{
				tmp->data = my_strcat(tmp->data, tmp->next->data);
				lst_pop(tmp->next, &token_list);
			}
		}
		tmp = tmp->next;
	}
}

/*
static size_t	matriochka_aux(t_token *elem, t_data *env_data, size_t i)
{
	char	*envar_name;
	char	*envar_value;
	char	*new_data;

	envar_name = ft_substr(elem->data, i,
			find_char_set(elem->data + i, "\t\n\v\f\r$ "));
	envar_value = find_envar(envar_name, env_data);
	new_data = ft_substr(elem->data, 0, ft_strlen(envar_value));
	new_data = my_strcat(new_data, envar_value);
	new_data = my_strcat(new_data,
			ft_substr(elem->data, i + ft_strlen(envar_name),
				ft_strlen(elem->data) - i - ft_strlen(envar_name)));
	free(envar_name);
	free(envar_value);
	free(elem->data);
	elem->data = new_data;
	return (ft_strlen(envar_value) - 1);
}


WARNING: MAY NOT BE USEFUL,
AS THERE MAY NOT BE ANY UNEXPANDED VAR INSIDE EXPORTED ONES!

Expand environement variables inside the already expanded ones, if present.
void	matriochka(t_token *elem, t_data *env_data)
{
	size_t	i;

	i = 0;
	while (elem->data[i])
	{
		if (elem->data[i] == '$'
			&& find_char_set(elem->data + i, "\t\n\v\f\r$ ") != 0)
		{
			i += matriochka_aux(elem, env_data, i);
		}
		++i;
	}
}
*/
