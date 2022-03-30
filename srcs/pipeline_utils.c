/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:00:24 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/30 12:01:08 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Removes the first string from the string array "cmd" in token elem.
Returns this string, or NULL if any error occurs.
*/
char	*pop_first_cmd(t_token *elem)
{
	char	*str;

	if (elem == NULL || elem->type != WORD || elem->cmd == NULL)
		return (NULL);
	str = elem->cmd[0];
	elem->cmd = elem->cmd + 1;
	return (str);
}

/*
Removes the last string from the string array "cmd" in token elem.
Returns this string, or NULL if any error occurs.
*/
char	*pop_last_cmd(t_token *elem)
{
	char	*str;
	size_t	i;

	if (elem == NULL || elem->type != WORD || elem->cmd == NULL)
		return (NULL);
	while (elem->cmd[i + 1] != NULL)
		++i;
	str = elem->cmd[i];
	elem->cmd[i] = NULL;
	return (str);
}
