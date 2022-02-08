/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:31:10 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/08 21:52:38 by smagdela         ###   ########.fr       */
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
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	END
}	t_token_type;

# define SPECIAL_CHARS "<>|\"\'"
# define TERM_CHARS " <>|\"\'"

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

/* Prototypes */
t_token	*lexer(char *input);
t_token	*scanner(const char *str);

size_t	find_char_set(const char *str, char *charset);

int		free_toklist(t_token *list);

bool	create_token(t_token_type type, char *data, t_token **list);
bool	categorizer(const char *str, t_token **token_list, size_t *i);

void	display_n_free(t_token *token_list);

int		categ_1(const char *str, t_token **token_list, size_t *i);
int		categ_2(const char *str, t_token **token_list, size_t *i);
int		categ_3(const char *str, t_token **token_list, size_t *i);
int		categ_4(const char *str, t_token **token_list, size_t *i);
int		categ_5(const char *str, t_token **token_list, size_t *i);


#endif
