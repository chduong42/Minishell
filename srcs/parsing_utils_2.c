/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:46:59 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/04 18:48:12 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
