/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:47:56 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/19 19:08:24 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_handler(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (pipe(tmp->pipefd) == -1)
				perror("MiniShell: Pipe failed");
			else
			{
				if (tmp->previous->out != -1)
					close(tmp->previous->out);
				tmp->previous->out = tmp->pipefd[1];
				if (tmp->next->in != -1)
					close(tmp->next->in);
				tmp->next->in = tmp->pipefd[0];
			}
		}
		tmp = tmp->next;
	}
}

void	file_handler(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		if (is_redir_token(tmp) == true && tmp->next != NULL)
		{
			tmp->heredoc_expand = tmp->next->heredoc_expand;
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
			heredoc(tmp->cmd[0], &tmp, data);
		else if (tmp->type == DGREAT && tmp->cmd != NULL)
			dgreat_handler(get_filepath(&tmp->cmd[0]), &tmp, data);
		tmp = tmp->next;
	}
}

char	*get_filepath(char **filename)
{
	char	*pwd;
	char	*filepath;

	if (*filename == NULL)
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

static void	executor_aux(char **envp, t_data *data, pid_t *exit_process)
{
	t_token	*tmp;
	int		nb_process;
	int		i;

	nb_process = count_cmd(data);
	tmp = data->token_list;
	*exit_process = 0;
	i = 0;
	while (tmp && *exit_process != -1 && i < nb_process)
	{
		if (tmp->type == WORD && tmp->cmd != NULL)
		{
			tmp->pid = fork_exec(tmp, envp, data);
			*exit_process = tmp->pid;
		}
		tmp = tmp->next;
	}
	tmp = data->token_list;
	while (nb_process != 1 && tmp && tmp->pid != *exit_process)
	{
		if (tmp->type == WORD && tmp->pid != -1)
			waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
}

/*
Launch the execution of the whole token_list, and frees it.
Reproduce the behavior of multiple pipes, adding file redirectors too.
*/
void	executor(char **envp, t_data *data)
{
	pid_t	exit_process;
	int		wstatus;

	if (data->token_list == NULL)
		return ;
	if (data->token_list->next == NULL)
		exit_process = fork_exec(data->token_list, envp, data);
	else
	{
		pipe_handler(data);
		file_handler(data);
		executor_aux(envp, data, &exit_process);
	}
	wstatus = 0;
	g_status = 1;
	if (exit_process != -1)
	{
		waitpid(exit_process, &wstatus, 0);
		if (WIFEXITED(wstatus))
			g_status = WEXITSTATUS(wstatus);
		if (WIFSIGNALED(wstatus))
			g_status = 128 + WTERMSIG(wstatus);
	}
	if (data->token_list)
		free_toklist(&data->token_list);
}
