/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:55:04 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/02 19:42:31 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	categ_1(const char *str, t_token *token_list, size_t *i)
{
	if (!ft_strncmp(&str[*i], "<<", 2))
	{
		if (create_token(DLESS, "<<", token_list) == FALSE)
			return (free_toklist(token_list));
		*i += 2;
		return (0);
	}
	else if (!ft_strncmp(&str[*i], "<", 2))
	{
		if (create_token(LESS, "<", token_list) == FALSE)
			return (free_toklist(token_list));
		++*i;
		return (0);
	}
	else if (!ft_strncmp(&str[*i], ">>", 2))
	{
		if (create_token(DGREAT, ">>", token_list) == FALSE)
			return (free_toklist(token_list));
		*i += 2;
		return (0);
	}
	return (1);
}

static int	categ_2(const char *str, t_token *token_list, size_t *i)
{
	char	*word_data;

	if (!ft_strncmp(&str[*i], ">", 2))
	{
		if (create_token(GREAT, ">", token_list) == FALSE)
			return (free_toklist(token_list));
		++*i;
		return (0);
	}
	else if (!ft_strncmp(&str[*i], "|", 2))
	{
		if (create_token(PIPE, "|", token_list) == FALSE)
			return (free_toklist(token_list));
		++*i;
		return (0);
	}
	else if (!ft_strncmp(&str[*i], "\"", 2) && find_char_set(&str[*i], "\""))
	{
		word_data = ft_substr(str, *i + 1, find_char_set(&str[*i], "\"") - 1);
		if (create_token(WORD, word_data, token_list) == FALSE)
			return (free_toklist(token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	return (1);
}

static int	categ_3(const char *str, t_token *token_list, size_t *i)
{
	char	*word_data;

	if (!ft_strncmp(&str[*i], "\"", 2) && !find_char_set(&str[*i], "\""))
	{
		word_data = ft_substr(str, *i, find_char_set(&str[*i], TERM_CHARS));
		if (create_token(WORD, word_data, token_list) == FALSE)
			return (free_toklist(token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	else if (!ft_strncmp(&str[*i], "\'", 2) && find_char_set(&str[*i], "\'"))
	{
		word_data = ft_substr(str, *i + 1, find_char_set(&str[*i], "\'") - 1);
		if (create_token(WORD, "\'", token_list) == FALSE)
			return (free_toklist(token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	return (1);
}

static int	categ_4(const char *str, t_token *token_list, size_t *i)
{
	char	*word_data;

	if (!ft_strncmp(&str[*i], "\'", 2) && !find_char_set(&str[*i], "\'"))
	{
		word_data = ft_substr(str, *i, find_char_set(&str[*i], TERM_CHARS));
		if (create_token(WORD, word_data, token_list) == FALSE)
			return (free_toklist(token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	else if (str[*i] == ' ')
	{
		++*i;
		return (0);
	}
	else
	{
		word_data = ft_substr(str, *i, find_char_set(&str[*i], SPECIAL_CHARS));
		if (create_token(WORD, word_data, token_list) == FALSE)
			return (free_toklist(token_list));
		*i += ft_strlen(word_data);
		return (0);
	}
	return (1);
}

t_bool	categorizer(const char *str, t_token *token_list, size_t *i)
{
	int	ret;

	ret = categ_1(str, token_list, i);
	if (ret == 0)
		return (TRUE);
	else if (ret == -1)
		return (FALSE);
	ret = categ_2(str, token_list, i) == FALSE;
	if (ret == 0)
		return (TRUE);
	else if (ret == -1)
		return (FALSE);
	ret = categ_3(str, token_list, i) == FALSE;
	if (ret == 0)
		return (TRUE);
	else if (ret == -1)
		return (FALSE);
	ret = categ_4(str, token_list, i) == FALSE;
	if (ret == 0)
		return (TRUE);
	else if (ret == -1)
		return (FALSE);
	return (free_toklist(token_list));
}
