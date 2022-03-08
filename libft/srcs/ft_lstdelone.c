/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:54:00 by chduong           #+#    #+#             */
/*   Updated: 2022/03/07 22:54:00 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list *prev;
	t_list *next;

	if (!lst || !del)
		return ;
	del(lst->line);
	del(lst->var);
	del(lst->content);
	prev = lst->prev;
	next = lst->next;
	prev->next = next;
	next->prev = prev;
	free(lst);
	lst = NULL;
}
