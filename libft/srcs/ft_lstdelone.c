/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:54:00 by chduong           #+#    #+#             */
/*   Updated: 2022/03/31 20:16:23 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list *prev;
	t_list *next;

	prev = lst->prev;
	next = lst->next;
	if (!lst || !del)
		return ;
	if (lst->line)
		del(lst->line);
	if (lst->var)
		del(lst->var);
	if (lst->value)
		del(lst->value);
	free(lst);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}
