/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:51:15 by kennyduong        #+#    #+#             */
/*   Updated: 2022/03/30 14:20:00 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cd(char *path, t_data *data)
{
    if (!path)
    {
        if (getenv("HOME"))
            chdir(getenv("HOME"));
        else
            printf("Minishell: cd: HOME not set\n");
        perror("Error");
    }
    else if (ft_strncmp(path, "./", 2) == 0)
    {
        if (path + 2)
    }
    else if (ft_strncmp(path, "../", 2) == 0)
    {
        
    }
    else
        chdir(path);
}