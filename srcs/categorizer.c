/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:55:04 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/03 15:28:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Redirections 1 category.
*/
static int	categ_1(const char *str, t_token **token_list, size_t *i)
{
	if (!ft_strncmp(&str[*i], "<<", 2))
	{
		if (create_token(DLESS, "<<", token_list) == FALSE)
			return (free_toklist(*token_list));
		*i += 2;
		return (0);
	}
	else if (!ft_strncmp(&str[*i], "<", 2))
	{
		if (create_token(LESS, "<", token_list) == FALSE)
			return (free_toklist(*token_list));
		++*i;
		return (0);
	}
	else if (!ft_strncmp(&str[*i], ">>", 2))
	{
		if (create_token(DGREAT, ">>", token_list) == FALSE)
			return (free_toklist(*token_list));
		*i += 2;
		return (0);
	}
	return (1);
}

/*
Redirections 2 category.
*/
static int	categ_2(const char *str, t_token **token_list, size_t *i)
{
	if (!ft_strncmp(&str[*i], ">", 2))
	{
		if (create_token(GREAT, ">", token_list) == FALSE)
			return (free_toklist(*token_list));
		++*i;
		return (0);
	}
	else if (!ft_strncmp(&str[*i], "|", 2))
	{
		if (create_token(PIPE, "|", token_list) == FALSE)
			return (free_toklist(*token_list));
		++*i;
		return (0);
	}
	return (1);
}

/*
Double quotes category.
*/
static int	categ_3(const char *str, t_token **token_list, size_t *i)
{
	char	*word_data;

	if (!ft_strncmp(&str[*i], "\"", 2) && find_char_set(&str[*i], "\""))
	{
		word_data = ft_substr(str, *i + 1, find_char_set(&str[*i], "\"") - 1);
		if (create_token(WORD, word_data, token_list) == FALSE)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	else if (!ft_strncmp(&str[*i], "\"", 2) && !find_char_set(&str[*i], "\""))
	{
		word_data = ft_substr(str, *i, find_char_set(&str[*i], TERM_CHARS));
		if (create_token(WORD, word_data, token_list) == FALSE)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	return (1);
}

/*
Simple quotes category.
*/
static int	categ_4(const char *str, t_token **token_list, size_t *i)
{
	char	*word_data;

	if (!ft_strncmp(&str[*i], "\'", 2) && find_char_set(&str[*i], "\'"))
	{
		word_data = ft_substr(str, *i + 1, find_char_set(&str[*i], "\'") - 1);
		if (create_token(WORD, "\'", token_list) == FALSE)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	else if (!ft_strncmp(&str[*i], "\'", 2) && !find_char_set(&str[*i], "\'"))
	{
		word_data = ft_substr(str, *i, find_char_set(&str[*i], TERM_CHARS));
		if (create_token(WORD, word_data, token_list) == FALSE)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	return (1);
}

/*
Non-special characters category.
*/
static int	categ_5(const char *str, t_token **token_list, size_t *i)
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
		if (create_token(WORD, word_data, token_list) == FALSE)
			return (free_toklist(*token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	return (1);
}

t_bool	categorizer(const char *str, t_token **token_list, size_t *i)
{
	int	ret;

	if ((ret = categ_1(str, token_list, i)) == 0)
		return (TRUE);
	else if (ret == -1)
		return (FALSE);
	if ((ret = categ_2(str, token_list, i)) == 0)
		return (TRUE);
	else if (ret == -1)
		return (FALSE);
	if ((ret = categ_3(str, token_list, i)) == 0)
		return (TRUE);
	else if (ret == -1)
		return (FALSE);
	if ((ret = categ_4(str, token_list, i)) == 0)
		return (TRUE);
	else if (ret == -1)
		return (FALSE);
	if ((ret = categ_5(str, token_list, i)) == 0)
		return (TRUE);
	else if (ret == -1)
		return (FALSE);
	free_toklist(*token_list);
	return (FALSE);
}
