/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:37:46 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/20 16:37:58 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_data *data)
{
	int		count;
	t_token	*tmp;

	count = 0;
	if (data == NULL || data->token_list == NULL)
		return (0);
	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->cmd != NULL)
			++count;
		tmp = tmp->next;
	}
	return (count);
}

char	*get_filepath(char **filename)
{
	char	*pwd;
	char	*filepath;

	if (filename == NULL || *filename == NULL)
		return (NULL);
	if (*filename[0] == '/')
		return (*filename);
	pwd = getcwd(NULL, 0);
	filepath = path_join(pwd, *filename);
	free(pwd);
	pwd = NULL;
	free(*filename);
	*filename = NULL;
	return (filepath);
}

void	check_exit_status(void)
{
	if (g_status == (128 | SIGQUIT))
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (g_status == (128 | SIGSEGV))
		ft_putstr_fd("Segmentation fault (core dumped)\n",
			STDERR_FILENO);
	else if (g_status == (128 | SIGINT))
		ft_putchar_fd('\n', STDERR_FILENO);
}
