/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:06:51 by chduong           #+#    #+#             */
/*   Updated: 2022/03/21 17:17:34 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	init_env(t_data *data, char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		ft_lstadd_back(&data->env, ft_lstnew(envp[i], tmp[0], tmp[1]));
		free_tab(tmp);
		++i;
	}
}

void	create_env(t_data *data)
{
	char	*tmp;
	char	*cwd;
	int		len;
	
	cwd = getcwd(NULL, 0);
	len = ft_strlen(cwd);
	tmp = malloc(sizeof(char) * (len + 5));
	ft_strlcpy(tmp, "PWD=", 5);
	ft_strlcat(tmp, cwd, len + 5);
	ft_lstadd_back(&data->env, ft_lstnew(tmp, "PWD", cwd));
	free(tmp);
	free(cwd);
	ft_lstadd_back(&data->env, ft_lstnew("SHLVL=1", "SHLVL", "1"));
	ft_lstadd_back(&data->env, ft_lstnew("_=/usr/bin/env", "_", "/usr/bin/env"));
}

void	data_init(t_data *data, char **envp)
{
	data->line = NULL;
	data->env = NULL;
	data->export = NULL;
	data->newenv = 0;
	data->newpath = 0;
	data->path = ft_split(getenv("PATH"), ':');
	if (*envp)
		init_env(data, envp);
	else
		create_env(data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	// t_token	*token_list;

	if (ac == 1)
	{
		data_init(&data, envp);
		ft_print_title();
		while (1)
		{
			data.line = readline("\e[1;35mMiniShell >: \e[0m");
			if (data.line && *data.line)
			{
				add_history(data.line);
				// token_list = lexer(data.line);
				// printf("Tokenizer output :\n");
				// display_toklist(token_list);
				// token_list = analyzer(token_list, &data);
				// printf("Analyzer output :\n");
				// display_toklist(token_list);
				// free_toklist(token_list);
				parse_line(envp, &data);
				free(data.line);
				data.line = NULL;
			}
		}
	}
	else
		printf("\e[1;37mUsage:\e[0m %s runs without any argument\n", av[0]);
	return (0);
}
