/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:54:00 by chduong           #+#    #+#             */
/*   Updated: 2022/03/15 16:28:49 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->line)
		del(lst->line);
	if (lst->var)
		del(lst->var);
	if (lst->content)
		del(lst->content);
	free(lst);
	lst = NULL;
}
