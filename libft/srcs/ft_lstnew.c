/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:21:12 by chduong           #+#    #+#             */
/*   Updated: 2022/03/28 15:12:06 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *envp, char *var, char *content)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	if (!a)
		return (NULL);
	a->line = NULL;
	a->var = NULL;
	a->content = NULL;
	if (envp)
		a->line = ft_strdup(envp);
	if (var)
		a->var = ft_strdup(var);
	if (content)
		a->content = ft_strdup(content);
	a->prev = NULL;
	a->next = NULL;
	return (a);
}
