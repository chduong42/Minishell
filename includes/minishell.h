/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:47 by chduong           #+#    #+#             */
/*   Updated: 2022/02/02 12:52:42 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/* Boolean type definition */
typedef uint8_t	t_bool;
# define TRUE 1
# define FALSE 0

int		parse_line(const char *line, char *path, char **env);
int		count_arg(char **arg);

void	exec_cmd(char **arg, char *path, char **env);
void	exit_shell(char **arg);

#endif