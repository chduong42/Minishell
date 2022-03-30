/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:08:07 by chduong           #+#    #+#             */
/*   Updated: 2022/03/30 14:19:04 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_digit(char *arg)
{
	if (*arg == '-')
		return (1);
	if (*arg == '+')
		++arg;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static void	clear_list(t_list **list)
{
	t_list	*tmp;
	t_list	*to_free;

	tmp = *list;
	while (tmp)
	{
		if (tmp->content)
			free(tmp->content);
		if (tmp->var)
			free(tmp->var);
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
		to_free = NULL;
	}
	*list = NULL;
}

void	free_exit(t_data *data, int opt)
{
	if (data->line)
		free(data->line);
	if (data->path)
		free_tab(data->path);
	if (data->export)
		free_tab(data->export);
	if (data->env)
		clear_list(&data->env);
	if (data->token_list)
		free_toklist(&data->token_list);
	clear_history();
	exit(opt);
}

void	exit_ms(char **arg, t_data *data)
{
	int	nb_arg;

	nb_arg = count_str(arg);
	if (nb_arg == 1)
	{
		printf("exit\n");
		free_exit(data, EXIT_SUCCESS);
	}
	else if (nb_arg == 2)
	{
		if (only_digit(arg[1]))
		{
			printf("exit\n");
			free_exit(data, ft_atoi(arg[1]));
		}
		else
		{
			printf("Minishell: exit: %s: numeric argument required\n", arg[1]);
			free_exit(data, 2);
		}
	}
	else
		printf("Minishell: exit: too many argument\n");
}
