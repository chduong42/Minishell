/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:47 by chduong           #+#    #+#             */
/*   Updated: 2022/03/28 14:47:37 by smagdela         ###   ########.fr       */
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

# define TERM_CHARS "<>|\"\'$"
# define TERM_N_SPACE " <>|\"\'$"

/* Data structures */
typedef enum e_token_type
{
	NONE,
	WORD,
	VAR,
	DQUOTE,
	SQUOTE,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
}	t_token_type;
/*
Note that only WORD and VAR token have malloc'd data attributes.
*/

typedef struct s_token
{
	size_t			index;
	char			*data;
	t_token_type	type;
	char			**cmd;
	bool			to_delete;
	int				pipefd[2];
	int				in;
	int				out;
	int				err;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_input
{
	const char	*str;
	size_t		index;
}	t_input;

typedef struct s_data
{
	char	*line;
	char	**path;
	char	**export;
	bool	newenv;
	bool	newpath;
	t_list	*env;
	t_token	*token_list;
}			t_data;

//	UTILS
void	ft_print_title(void);
void	free_tab(char **tab);
void	sort_export(char **sort);

char	**cpy_env(t_list *env);

// DATA INIT
void	new_export(t_data *data);
void	new_path(t_data *data);
void	data_init(t_data *data, char **envp);

int		count_str(char **str);

bool	is_in_charset(char c, char *charset);
bool	ft_is_in_charset(char c, char *charset);

t_list	*grep(t_list *env, char *varname);

char	*my_strcat(char *dest, char *str);
char	*cleaner(char *str_in);

size_t	find_char_set(const char *str, char *charset);

//	PARSING
t_token	*lexer(char *input);
t_token	*scanner(const char *str);
t_token	*analyzer(t_token *token_list, t_data *env_data);

int		free_toklist(t_token **list);
int		categ_1(t_input *input, t_token **token_list);
int		categ_2(t_input *input, t_token **token_list);
int		categ_3(t_input *input, t_token **token_list);
int		categ_4(t_input *input, t_token **token_list);
int		categ_5(t_input *input, t_token **token_list);

char	*find_envar(char *envar, t_data *env_data);

size_t	ft_envarlen(const char *str);
size_t	is_closed(t_token *elem, t_token_type elem_type);

bool	create_token(t_token_type type, char *data, t_token **list);
bool	categorizer(t_input *input, t_token **token_list);
bool	checker_quotes(t_token *token_list, t_data *env_data);
bool	checker_words(t_token *token_list);
bool	reduce_words(t_token *elem, size_t end, t_token *token_list);
bool	checker_redir(t_token *token_list);

void	display_toklist(t_token *token_list);
void	relink_toklist(t_token *elem, t_token *tmp,
			char *new_data, t_token **token_list);
void	expand(t_token *elem, t_data *env_data);
void	lst_pop(t_token *elem, t_token **token_list);
void	reduce_all(t_token *elem, t_token *end, t_token *token_list);
void	reduce(t_token *elem, t_token *end, t_data *env_data,
			t_token *token_list);
void	expand_remaining_envar(t_token *token_list, t_data *env_data);
void	suppress_spaces(t_token **token_list);

//	EXEC
bool	executor(char **envp, t_data *data);
void	fork_exec(t_token *elem, char **envp, t_data *data);

t_list	*grep(t_list *env, char *varname);

//	BUILTINS
void	echo(char **arg);
void	exit_ms(char **arg, t_data *data);
void	export(char **arg, t_data *data);
void	env(t_list *env);
void	pwd(void);
void	unset(char **arg, t_data *data);

#endif
