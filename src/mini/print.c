/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/25 11:02:54 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../pipe/pipex.h"
#include "mini.h"
#include <stdlib.h>

int main(int argc, char **argv, char **envp) 
{
	t_data *data;
	(void)argv;
	(void)argc;
	int result;

	result = 0;
	data = malloc(sizeof(t_data));
	init_node_env(data, envp);
	data->last_pid = 0;
	data->path = NULL;
	while (1)
	{
		init_env(data);
		setup_readline_signals();
		if (isatty(fileno(stdin)))
        		data->str = readline("Minishell: ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			data->str = ft_strtrim(line, "\n");
			free(line);
		}
		after_readline_signals();
        if (data->str == NULL)
            return (0);
		if (init_cmd(data, data->str))
			result = init_pip(data);
		ft_lstclear_cmd(data->cmd);
		free(data->str);
	}
	if (data->cmd->fd_rdoc != 0)
		close(data->cmd->fd_rdoc);

	return (ft_lstclear_data(data));
}





int status_one_cmd(pid_t pid)
{
 	int status;

	status = 0;
	if (waitpid(pid, &status, 0) == -1)
			return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
    	int signal = WTERMSIG(status);
        return (128 + signal);
	}
	return (-1);
}


