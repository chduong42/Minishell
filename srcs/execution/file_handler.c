/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:52:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/04 17:51:52 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	end_handlers(char *filepath, t_token **tmp, t_data *data)
{
	free(filepath);
	filepath = NULL;
	if ((*tmp)->previous)
	{
		*tmp = (*tmp)->previous;
		lst_pop((*tmp)->next, &data->token_list);
		merge_cmd(*tmp, data);
	}
}

static void	less_handler(char *filepath, t_token **tmp, t_data *data)
{
	int		fd;

	if (access(filepath, R_OK) == 0)
	{
		fd = open(filepath, O_RDONLY);
		if ((*tmp)->previous == NULL)
		{
			if ((*tmp)->next->in != -1)
				close((*tmp)->next->in);
			(*tmp)->next->in = fd;
		}
		else
		{
			if ((*tmp)->previous->in != -1)
				close((*tmp)->previous->in);
			(*tmp)->previous->in = fd;
		}
	}
	else
		perror("MiniShell: Error");
	end_handlers(filepath, tmp, data);
}

static void	great_handler(char *filepath, t_token **tmp, t_data *data)
{
	int		fd;

	if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
	{
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if ((*tmp)->previous->out != -1)
			close((*tmp)->previous->out);
		(*tmp)->previous->out = fd;
	}
	else
		perror("MiniShell: Error");
	end_handlers(filepath, tmp, data);
}

static void	dgreat_handler(char *filepath, t_token **tmp, t_data *data)
{
	int		fd;

	if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
	{
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if ((*tmp)->previous->out != -1)
			close((*tmp)->previous->out);
		(*tmp)->previous->out = fd;
	}
	else
		perror("MiniShell: Error");
	end_handlers(filepath, tmp, data);
}

void	file_handler(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == LESS || tmp->type == DLESS
			|| tmp->type == GREAT || tmp->type == DGREAT)
		{
			tmp->cmd = malloc(sizeof(char *) * 2);
			if (tmp->cmd == NULL)
				return (perror("MiniShell: malloc failed"));
			tmp->cmd[0] = pop_first_cmd(&(tmp->next), data);
			tmp->cmd[1] = NULL;
		}
		if (tmp->type == LESS && tmp->cmd != NULL)
			less_handler(get_filepath(&tmp->cmd[0]), &tmp, data);
		else if (tmp->type == GREAT && tmp->cmd != NULL)
			great_handler(get_filepath(&tmp->cmd[0]), &tmp, data);
		else if (tmp->type == DLESS && tmp->cmd != NULL)
			heredoc(tmp->cmd[0]);
		else if (tmp->type == DGREAT && tmp->cmd != NULL)
			dgreat_handler(get_filepath(&tmp->cmd[0]), &tmp, data);
		tmp = tmp->next;
	}
}
