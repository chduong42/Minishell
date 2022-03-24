/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:47 by chduong           #+#    #+#             */
/*   Updated: 2022/03/24 15:45:30 by kennyduong       ###   ########.fr       */
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
char	**cpy_env(t_list *env);

//	PARSING
void	data_init(t_data *data, char **envp);
void	parse_line(char **arg, char **envp, t_data *data);

t_list	*grep(t_list *env, char *varname);

//	BUILTINS
void	echo(char **arg);
void	exit_ms(char **arg, t_data *data);
void	export(char **arg, t_data *data);
void	fork_exec(char **arg, char **envp, t_data *data);
void	print_env(t_list *env);
void	print_export(t_data *data);
void	pwd(void);
void	unset(char **arg, t_data *data);

#endif
