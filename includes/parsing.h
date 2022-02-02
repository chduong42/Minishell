/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:31:10 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/02 19:11:41 by smagdela         ###   ########.fr       */
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
	SQUOTE,
	DQUOTE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	END
}	t_token_type;

# define SPECIAL_CHARS "<>|\"\'"
# define TERM_CHARS " <>|"

typedef enum e_abstract_type
{
	NONE,
	PROGRAM,
	COMMAND,
	OPTION,
	ARGUMENT,
	REDIRECT,
	EXPANSION
}	t_abstract_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

/* Prototypes */
t_bool	lexer(char *input, t_token *token_list);
int		free_toklist(t_token *list);
t_bool	categorizer(char *str, t_token *token_list, size_t *i);

#endif
