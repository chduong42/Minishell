/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorizer_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 21:42:47 by smagdela          #+#    #+#             */
/*   Updated: 2022/02/11 16:07:59 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	categorizer(t_input *input, t_token **token_list)
{
	int	ret;

	if ((ret = categ_1(input, token_list)) == 0)
		return (true);
	else if (ret == -1)
		return (false);
	if ((ret = categ_2(input, token_list)) == 0)
		return (true);
	else if (ret == -1)
		return (false);
	if ((ret = categ_3(input, token_list)) == 0)
		return (true);
	else if (ret == -1)
		return (false);
	if ((ret = categ_4(input, token_list)) == 0)
		return (true);
	else if (ret == -1)
		return (false);
	if ((ret = categ_5(input, token_list)) == 0)
		return (true);
	else if (ret == -1)
		return (false);
	free_toklist(*token_list);
	return (false);
}

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
