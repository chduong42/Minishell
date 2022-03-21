/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:55:04 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/21 12:30:39 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Redirections 1 category.
*/
int	categ_1(t_input *input, t_token **token_list)
{
	if (!ft_strncmp(&input->str[input->index], "<<", 2))
	{
		if (create_token(DLESS, "<<", token_list) == false)
			return (free_toklist(*token_list));
		input->index += 2;
		return (0);
	}
	else if (input->str[input->index] == '<')
	{
		if (create_token(LESS, "<", token_list) == false)
			return (free_toklist(*token_list));
		++input->index;
		return (0);
	}
	else if (!ft_strncmp(&input->str[input->index], ">>", 2))
	{
		if (create_token(DGREAT, ">>", token_list) == false)
			return (free_toklist(*token_list));
		input->index += 2;
		return (0);
	}
	return (1);
}

/*
Redirections 2 category.
*/
int	categ_2(t_input *input, t_token **token_list)
{
	if (input->str[input->index] == '>')
	{
		if (create_token(GREAT, ">", token_list) == false)
			return (free_toklist(*token_list));
		++input->index;
		return (0);
	}
	else if (input->str[input->index] == '|')
	{
		if (create_token(PIPE, "|", token_list) == false)
			return (free_toklist(*token_list));
		++input->index;
		return (0);
	}
	return (1);
}

/*
Quotes and spaces category.
*/
int	categ_3(t_input *input, t_token **token_list)
{
	if (input->str[input->index] == 34)
	{
		if (!input->squoted)
			input->dquoted = !input->dquoted;
		if (create_token(DQUOTE, "\"", token_list) == false)
			return (free_toklist(*token_list));
		++input->index;
		return (0);
	}
	else if (input->str[input->index] == 39)
	{
		if (!input->dquoted)
			input->squoted = !input->squoted;
		if (create_token(SQUOTE, "\'", token_list) == false)
			return (free_toklist(*token_list));
		++input->index;
		return (0);
	}
	else if (input->str[input->index] == ' '
		&& !input->squoted && !input->dquoted)
	{
		++input->index;
		return (0);
	}
	return (1);
}

/*
Env variables.
*/
int	categ_4(t_input *input, t_token **token_list)
{
	char	*word_data;

	if (input->str[input->index] == '$')
	{
		if (input->str[input->index + 1] == '$'
			|| input->str[input->index + 1] == '\0')
		{
			if (create_token(WORD, ft_strdup("$"), token_list) == false)
				return (free_toklist(*token_list));
			++input->index;
			return (0);
		}
		word_data = ft_substr(input->str, input->index,
				ft_envarlen(input->str + input->index));
		if (create_token(VAR, word_data, token_list) == false)
			return (free_toklist(*token_list));
		input->index += ft_strlen(word_data);
		return (0);
	}
	return (1);
}

/*
Non-special characters category.
*/
int	categ_5(t_input *input, t_token **token_list)
{
	char	*word_data;
	char	*charset;

	if (input->dquoted || input->squoted)
		charset = TERM_CHARS;
	else
		charset = TERM_N_SPACE;
	if (find_char_set(&input->str[input->index], charset) != 0)
		word_data = ft_substr(input->str, input->index,
				find_char_set(&input->str[input->index], charset));
	else
		word_data = ft_substr(input->str, input->index,
				ft_strlen(&input->str[input->index]));
	if (create_token(WORD, word_data, token_list) == false)
		return (free_toklist(*token_list));
	input->index += ft_strlen(word_data);
	return (0);
}
