/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:31:10 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/23 11:39:20 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

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
# define TERM_CHARS "<>|\"\'$"
# define TERM_N_SPACE " <>|\"\'$"

typedef struct s_token
{
	size_t			index;
	char			*data;
	t_token_type	type;
	char			**cmd;
	bool			to_delete;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_input
{
	const char	*str;
	size_t		index;
}	t_input;

/* Prototypes */
t_token	*lexer(char *input);
t_token	*scanner(const char *str);
t_token	*analyzer(t_token *token_list, t_data *env_data);

char	*my_strcat(char *dest, char *str);
char	*find_envar(char *envar, t_data *env_data);
char	*cleaner(char *str_in);

size_t	find_char_set(const char *str, char *charset);
size_t	is_closed(t_token *elem, t_token_type elem_type);
size_t	ft_envarlen(const char *str);

int		free_toklist(t_token *list);

bool	ft_is_in_charset(char c, char *charset);
bool	create_token(t_token_type type, char *data, t_token **list);
bool	categorizer(t_input *input, t_token **token_list);
bool	checker_quotes(t_token *token_list, t_data *env_data);
bool	checker_words(t_token *token_list);
bool	reduce_words(t_token *elem, size_t end, t_token *token_list);
bool	checker_redir(t_token *token_list);
bool	executor(t_token *token_list, char **envp, t_data *data);

void	display_toklist(t_token *token_list);
void	relink_toklist(t_token *elem, t_token *tmp,
			char *new_data, t_token **token_list);
void	expand(t_token *elem, t_data *env_data);
void	lst_pop(t_token *elem, t_token **token_list);
void	reduce_all(t_token *elem, t_token *end, t_token *token_list);
void	reduce(t_token *elem, t_token *end, t_data *env_data,
			t_token *token_list);
void	ft_print_title(void);
void	expand_remaining_envar(t_token *token_list, t_data *env_data);
void	suppress_spaces(t_token **token_list);

int		categ_1(t_input *input, t_token **token_list);
int		categ_2(t_input *input, t_token **token_list);
int		categ_3(t_input *input, t_token **token_list);
int		categ_4(t_input *input, t_token **token_list);
int		categ_5(t_input *input, t_token **token_list);

#endif
