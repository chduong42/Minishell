/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:47 by chduong           #+#    #+#             */
/*   Updated: 2022/02/17 16:58:25 by chduong          ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

//	TYPEDEF
typedef struct s_data
{
	char	*line;
	char	**path;
	int		newenv;
	int		newpath;
	t_list	*env;
}			t_data;

//	UTILS
int		count_str(char **str);
void	free_tab(char **tab);
void	clear_memory(char *line, char **path);
bool	is_in_charset(char c, char *charset);

//	PARSING
void	parse_line(t_data *data);

//	BUILTINS
void	exit_shell(char **arg, char *line, char **path);
void	exec_cmd(char **arg, char **path, char **env);
void	print_env(char **env);
void	print_export(char **env);

#endif