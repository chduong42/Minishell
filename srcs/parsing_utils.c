/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:26:15 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/09 15:32:42 by smagdela         ###   ########.fr       */
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
	if (dest != NULL)
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

static char	*find_envar_aux(t_list *tmp, size_t env_var_len)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char)
			* (ft_strlen(tmp->content) - env_var_len - 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, tmp->content + env_var_len + 1,
		ft_strlen(tmp->content) - env_var_len - 1);
	return (ret);
}

/*
Finds "envar" in "envp" and returns its value,
according to the environment format.
If no envar with such a name exists, returns an empty string "".
Even if empty, the string is malloc'd, so that double frees won't happen.
Treats special envar like $?.
Returns NULL in case an error occured.
*/
char	*find_envar(char *envar, t_data *env_data)
{
	char	*ret;
	t_list	*tmp;
	size_t	envar_len;
	size_t	env_var_len;

	tmp = env_data->env;
	envar_len = ft_strlen(envar);
	while (tmp != NULL)
	{
		env_var_len = find_char_set(tmp->content, "=");
		if (envar_len == env_var_len
			&& ft_strncmp(tmp->content, envar, ft_strlen(envar)) == 0)
		{
			return (find_envar_aux(tmp, env_var_len));
		}
		tmp = tmp->next;
	}
	ret = malloc(1);
	if (ret == NULL)
		return (NULL);
	ret[0] = '\0';
	return (ret);
}

void	lst_pop(t_token *elem)
{
	t_token	*tmp;

	if (elem == NULL)
		return ;
	if (elem->type == WORD || elem->type == VAR)
		free(elem->data);
	if (elem->next != NULL)
		elem->next->previous = elem->previous;
	if (elem->previous != NULL)
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
	free(elem);
	elem = NULL;
}
