/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:47:38 by chduong           #+#    #+#             */
/*   Updated: 2022/02/08 17:34:00 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		++env;
	}
}

void	print_export(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		++env;
	}
}
