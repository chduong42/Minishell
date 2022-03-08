/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:03:04 by chduong           #+#    #+#             */
/*   Updated: 2022/02/18 14:25:22 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;
	
	if (!alst)
		return ;
	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->prev = last;
	}
}
