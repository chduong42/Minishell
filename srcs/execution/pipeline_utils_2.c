/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:37:46 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/08 12:40:24 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_data *data)
{
	int		count;
	t_token	*tmp;

	count = 0;
	if (data == NULL || data->token_list == NULL)
		return (0);
	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->cmd != NULL)
			++count;
		tmp = tmp->next;
	}
	return (count);
}
