/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:17:23 by chduong           #+#    #+#             */
/*   Updated: 2022/03/24 13:32:34 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options*/

/*
Receives the char **arg variable, containing 
*/
void	parse_line(char **arg, char **envp, t_data *data)
{
	//if (ft_strncmp(arg[0], "cd", 3) == 0)
	//	cd();
	if (ft_strncmp(arg[0], "echo", 5) == 0)
		echo(arg);
	else if (ft_strncmp(arg[0], "env", 4) == 0)
		print_env(data->env);
	else if (ft_strncmp(arg[0], "exit", 5) == 0)
		exit_ms(arg, data);
	else if (ft_strncmp(arg[0], "export", 7) == 0)
		export(arg, data);
	else if (ft_strncmp(arg[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(arg[0], "unset", 6) == 0)
		unset(arg, data);
	else
		fork_exec(arg, envp, data);
}
