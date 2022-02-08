/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:55:04 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/08 21:51:56 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Redirections 1 category.
*/
int	categ_1(const char *str, t_token **token_list, size_t *i)
{
	if (!ft_strncmp(&str[*i], "<<", 2))
	{
		if (create_token(DLESS, "<<", token_list) == false)
			return (free_toklist(*token_list));
		*i += 2;
		return (0);
	}
	else if (str[*i] == '<')
	{
		if (create_token(LESS, "<", token_list) == false)
			return (free_toklist(*token_list));
		++*i;
		return (0);
	}
	else if (!ft_strncmp(&str[*i], ">>", 2))
	{
		if (create_token(DGREAT, ">>", token_list) == false)
			return (free_toklist(*token_list));
		*i += 2;
		return (0);
	}
	return (1);
}

/*
Redirections 2 category.
*/
int	categ_2(const char *str, t_token **token_list, size_t *i)
{
	if (str[*i] == '>')
	{
		if (create_token(GREAT, ">", token_list) == false)
			return (free_toklist(*token_list));
		++*i;
		return (0);
	}
	else if (str[*i] == '|')
	{
		if (create_token(PIPE, "|", token_list) == false)
			return (free_toklist(*token_list));
		++*i;
		return (0);
	}
	return (1);
}

/*
Double quotes category.
*/
int	categ_3(const char *str, t_token **token_list, size_t *i)
{
	char	*word_data;

	if (str[*i] == '"' && find_char_set(&str[*i], "\""))
	{
		word_data = ft_substr(str, *i + 1, find_char_set(&str[*i], "\"") - 1);
		if (create_token(WORD, word_data, token_list) == false)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data) + 2;
		return (0);
	}
	else if (str[*i] == '"' && !find_char_set(&str[*i], "\""))
	{
		word_data = ft_substr(str, *i, find_char_set(&str[*i], TERM_CHARS));
		if (create_token(WORD, word_data, token_list) == false)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	return (1);
}

/*
Simple quotes category.
*/
int	categ_4(const char *str, t_token **token_list, size_t *i)
{
	char	*word_data;

	if (str[*i] == 39 && find_char_set(&str[*i], "\'"))
	{
		word_data = ft_substr(str, *i + 1, find_char_set(&str[*i], "\'") - 1);
		if (create_token(WORD, word_data, token_list) == false)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data) + 2;
		return (0);
	}
	else if (str[*i] == 39 && !find_char_set(&str[*i], "\'"))
	{
		word_data = ft_substr(str, *i, find_char_set(&str[*i], TERM_CHARS));
		if (create_token(WORD, word_data, token_list) == false)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	return (1);
}

/*
Non-special characters category.
*/
int	categ_5(const char *str, t_token **token_list, size_t *i)
{
	char	*word_data;

	if (str[*i] == ' ')
	{
		++*i;
		return (0);
	}
	else
	{
		if (find_char_set(&str[*i], TERM_CHARS) != 0)
			word_data = ft_substr(str, *i, find_char_set(&str[*i], TERM_CHARS));
		else
			word_data = ft_substr(str, *i, ft_strlen(&str[*i]));
		if (create_token(WORD, word_data, token_list) == false)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	return (1);
}
