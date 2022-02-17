/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:47:38 by chduong           #+#    #+#             */
/*   Updated: 2022/02/09 21:21:26 by chduong          ###   ########.fr       */
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

static char	**cpy_env(char **env)
{
	char	**sort;
	int	i;
	
	sort = malloc(sizeof(char*) * (count_str(env) + 1));
	i = 0;
	while (env[i])
	{
		sort[i] = env[i];
		++i;
	}
	sort[i] = 0;
	return (sort);
}

void	print_export(char **env)
{
	char	**sort;
    char	*tmp;
	int		i;
	int		j;

	sort = cpy_env(env);
	i = 0;
	while (sort[i])
	{
		j = i + 1;
		while (sort[j])
		{
			if (ft_strncmp(sort[i], sort[j], ft_strlen(sort[i])) > 0)
			{
				tmp = sort[i];
				sort[i] = sort[j];
				sort[j] = tmp;
			}
			++j;
		}
		++i;
	}
	print_env(sort);
	free(sort);
}
