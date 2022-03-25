/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:40:03 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/25 14:45:14 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("[%s] ", tab[i]);
		++i;
	}
	printf("\n");
}

static void	type_display(t_token *tmp)
{
	if (tmp->type == WORD && tmp->cmd != NULL)
	{
		printf("%zu WORD (cmd) : ", tmp->index);
		print_tab(tmp->cmd);
	}
	else if (tmp->type == WORD && tmp->data != NULL)
		printf("%zu WORD (data) : [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == PIPE)
		printf("%zu PIPE: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == LESS)
		printf("%zu LESS: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == GREAT)
		printf("%zu GREAT: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == DLESS)
		printf("%zu DLESS: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == DGREAT)
		printf("%zu DGREAT: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == VAR)
		printf("%zu VAR: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == DQUOTE)
		printf("%zu DQUOTE: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == SQUOTE)
		printf("%zu SQUOTE: [%s]\n", tmp->index, tmp->data);
}

/*
Temporary function used to display the tokenlist ,
in order to check tokenizer's good behavior.
Erase it before defense, as it contains forbidden functions.
*/
void	display_toklist(t_token *token_list)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp != NULL)
	{
		type_display(tmp);
		tmp = tmp->next;
	}
}

/*
Deletes every WORD token which are only spaces.
*/
void	suppress_spaces(t_token **token_list)
{
	t_token	*tmp;
	t_token	*to_pop;

	tmp = *token_list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD
			&& !ft_strncmp(tmp->data, " ", ft_strlen(tmp->data))
			&& tmp->to_delete == true)
		{
			to_pop = tmp;
			tmp = tmp->next;
			lst_pop(to_pop, token_list);
		}
		else
			tmp = tmp->next;
	}
}

/*
static size_t	matriochka_aux(t_token *elem, t_data *env_data, size_t i)
{
	char	*envar_name;
	char	*envar_value;
	char	*new_data;

	envar_name = ft_substr(elem->data, i,
			find_char_set(elem->data + i, "\t\n\v\f\r$ "));
	envar_value = find_envar(envar_name, env_data);
	new_data = ft_substr(elem->data, 0, ft_strlen(envar_value));
	new_data = my_strcat(new_data, envar_value);
	new_data = my_strcat(new_data,
			ft_substr(elem->data, i + ft_strlen(envar_name),
				ft_strlen(elem->data) - i - ft_strlen(envar_name)));
	free(envar_name);
	free(envar_value);
	free(elem->data);
	elem->data = new_data;
	return (ft_strlen(envar_value) - 1);
}


WARNING: MAY NOT BE USEFUL,
AS THERE MAY NOT BE ANY UNEXPANDED VAR INSIDE EXPORTED ONES!

Expand environement variables inside the already expanded ones, if present.
void	matriochka(t_token *elem, t_data *env_data)
{
	size_t	i;

	i = 0;
	while (elem->data[i])
	{
		if (elem->data[i] == '$'
			&& find_char_set(elem->data + i, "\t\n\v\f\r$ ") != 0)
		{
			i += matriochka_aux(elem, env_data, i);
		}
		++i;
	}
}
*/
