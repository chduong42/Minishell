/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/04/19 18:13:15 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

static void	ft_print_title(void)
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

static void	prompt(t_data *data, char **envp)
{
	while (1)
	{
		data->line = readline(RL_PROMPT);
		if (data->line)
		{
			if (*data->line)
				add_history(data->line);
			data->token_list = lexer(data->line);
			if (data->token_list != NULL)
			{
				analyzer(data);
				if (data->token_list != NULL)
					executor(envp, data);
			}
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			free_exit(data, EXIT_SUCCESS);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	set_signal(DEFAULT);
	if (ac == 1)
	{
		data_init(&data, envp);
		ft_print_title();
		prompt(&data, envp);
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	return (0);
}
