/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:47 by chduong           #+#    #+#             */
/*   Updated: 2022/03/24 11:21:41 by smagdela         ###   ########.fr       */
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
# include <errno.h>
# include "libft.h"

# define PROMPT "\x1B[1;35mMiniShell >: \x1B[0m"
# define RL_PROMPT "MiniShell >: "

//	TYPEDEF
typedef struct s_data
{
	char	*line;
	char	**path;
	char	**export;
	bool	newenv;
	bool	newpath;
	t_list	*env;
}			t_data;

//	UTILS
int		count_str(char **str);
void	free_tab(char **tab);
bool	is_in_charset(char c, char *charset);
t_list	*grep(t_list *env, char *varname);

//	PARSING
void	parse_line(char **arg, char **envp, t_data *data);

//	BUILTINS
void	echo(char **arg);
void	exit_ms(char **arg, t_data *data);
void	fork_exec(char **arg, char **envp, t_data *data);
void	print_env(t_list *env);
void	print_export(t_data *data);
void	export(char **arg, t_data *data);
void	unset(char **arg, t_data *data);

#endif
