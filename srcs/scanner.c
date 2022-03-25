/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:31:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/25 14:45:14 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns true if "c" is in "charset", false otherwise.
*/
bool	is_in_charset(char c, char *charset)
{
	int		i;

	if (!charset || c == '\0')
		return (false);
	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		++i;
	}
	return (false);
}

static int	categorizer_aux(t_input *input, t_token **token_list)
{
	int	ret;

	ret = categ_1(input, token_list);
	if (ret != 1)
		return (ret);
	ret = categ_2(input, token_list);
	if (ret != 1)
		return (ret);
	ret = categ_3(input, token_list);
	if (ret != 1)
		return (ret);
	ret = categ_4(input, token_list);
	if (ret != 1)
		return (ret);
	ret = categ_5(input, token_list);
	if (ret != 1)
		return (ret);
	return (-1);
}

/*
Ask what category is the data from the input, and create token accordingly.
*/
bool	categorizer(t_input *input, t_token **token_list)
{
	int	ret;

	ret = categorizer_aux(input, token_list);
	if (ret == 0)
		return (true);
	free_toklist(*token_list);
	return (false);
}

/*
Core function of the lexer.
*/
t_token	*scanner(const char *str)
{
	t_token		*token_list;
	t_input		input;

	if (!str)
	{
		ft_putstr_fd("Error: Null string passed to scanner\n", 2);
		return (NULL);
	}
	token_list = NULL;
	input.str = str;
	input.index = 0;
	while (input.index < ft_strlen(str))
	{
		if (categorizer(&input, &token_list) == false)
			break ;
	}
	return (token_list);
}

/*
Printing introduction banner...
*/
void	ft_print_title(void)
{
	ft_putstr_fd("\n\033[0;92m::::     :::: ::::::::::: ::::    :::", 1);
	ft_putstr_fd(" ::::::::::: ::::::::  :::    ::: :::::::::: ::: ", 1);
	ft_putstr_fd("       :::             :::             \n", 1);
	ft_putstr_fd("+:+:+: :+:+:+     :+:     :+:+:   :+:     :+:    ", 1);
	ft_putstr_fd(":+:    :+: :+:    :+: :+:        :+:        :+:  ", 1);
	ft_putstr_fd("            :+:            \n", 1);
	ft_putstr_fd("+:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+    ", 1);
	ft_putstr_fd("+:+        +:+    +:+ +:+        +:+        +:+  ", 1);
	ft_putstr_fd("             +:+           \n", 1);
	ft_putstr_fd("+#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    ", 1);
	ft_putstr_fd("+#++:++#++ +#++:++#++ +#++:++#   +#+        +#+  ", 1);
	ft_putstr_fd("              +#+          \n", 1);
	ft_putstr_fd("+#+       +#+     +#+     +#+  +#+#+#     +#+    ", 1);
	ft_putstr_fd("       +#+ +#+    +#+ +#+        +#+        +#+  ", 1);
	ft_putstr_fd("	       +#+            \n", 1);
	ft_putstr_fd("#+#       #+#     #+#     #+#   #+#+#     #+#    ", 1);
	ft_putstr_fd("#+#    #+# #+#    #+# #+#        #+#        #+#  ", 1);
	ft_putstr_fd("            #+#            \n", 1);
	ft_putstr_fd("###       ### ########### ###    #### ###########", 1);
	ft_putstr_fd(" ########  ###    ### ########## ########## #####", 1);
	ft_putstr_fd("#####      ###    ##########\033[0;m\n\n", 1);
}
