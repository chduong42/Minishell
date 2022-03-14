/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:55:04 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/14 13:15:02 by smagdela         ###   ########.fr       */
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
Quotes category.
*/
int	categ_3(t_input *input, t_token **token_list)
{
	if (input->str[input->index] == 34)
	{
		if (create_token(DQUOTE, "\"", token_list) == false)
			return (free_toklist(*token_list));
		if (input->dquoted == false && input->squoted == false)
			input->dquoted = true;
		else if (input->dquoted == true)
			input->dquoted = false;
		++input->index;
		return (0);
	}
	else if (input->str[input->index] == 39)
	{
		if (create_token(SQUOTE, "\'", token_list) == false)
			return (free_toklist(*token_list));
		if (input->squoted == false && input->dquoted == false)
			input->squoted = true;
		else if (input->squoted == true)
			input->squoted = false;
		++input->index;
		return (0);
	}
	return (1);
}

/*
Env variables and spaces category.
*/
int	categ_4(t_input *input, t_token **token_list)
{
	char	*word_data;

	if (input->str[input->index] == '$')
	{
		if (input->str[input->index + 1] == '$')
		{
			if (create_token(WORD, ft_strdup("$"), token_list) == false)
				return (free_toklist(*token_list));
			return (0);
		}
		word_data = ft_substr(input->str, input->index,
				ft_envarlen(input->str + input->index));
		if (create_token(VAR, word_data, token_list) == false)
			return (free_toklist(*token_list));
		input->index += ft_strlen(word_data);
		return (0);
	}
	else if (input->str[input->index] == ' '
		&& input->dquoted == false && input->squoted == false)
	{
		++input->index;
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

	charset = TERM_N_SPACE;
	if (input->dquoted == true || input->squoted == true)
		charset = TERM_CHARS;
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
