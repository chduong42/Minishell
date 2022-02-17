/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:31:10 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/17 16:46:01 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* Data structures */
typedef enum e_token_type
{
	NONE,
	WORD,	// Note that only WORD and VAR tokens
	VAR,	// have malloc'd data attributes.
	DQUOTE,
	SQUOTE,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	END
}	t_token_type;

# define TERM_CHARS "<>|\"\'$"
# define TERM_N_SPACE " <>|\"\'$"

typedef enum e_abstract_type
{
	COMMAND,
	ARGUMENT,
	REDIRECT,
	EXPANSION
}	t_abstract_type;

typedef struct s_token
{
	size_t			index;
	char			*data;
	t_token_type	type;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_input
{
	const char	*str;
	size_t		index;
	bool		dquoted;
	bool		squoted;
}	t_input;

/* Prototypes */
t_token	*lexer(char *input);
t_token	*scanner(const char *str);
t_token	*analyzer(t_token *token_list);

char	*my_strcat(char *dest, char *str);
char	*find_envar(char *envar, char **envp);

size_t	find_char_set(const char *str, char *charset);

int		free_toklist(t_token *list);

bool	create_token(t_token_type type, char *data, t_token **list);
bool	categorizer(t_input *input, t_token **token_list);

void	display_toklist(t_token *token_list);
void	expand(t_token *elem);

int		categ_1(t_input *input, t_token **token_list);
int		categ_2(t_input *input, t_token **token_list);
int		categ_3(t_input *input, t_token **token_list);
int		categ_4(t_input *input, t_token **token_list);
int		categ_5(t_input *input, t_token **token_list);

#endif
