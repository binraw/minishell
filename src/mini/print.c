/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/23 14:52:52 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../pipe/pipex.h"
#include "mini.h"
#include <stdlib.h>

int main(int argc, char **argv, char **envp) 
{
	t_data vars;
	(void)argv;
	(void)argc;
	int result;

	result = 0;
	init_node_env(&vars, envp);
	vars.last_pid = 0;
	while (1)
	{
		init_env(&vars);
		setup_readline_signals();
		if (isatty(fileno(stdin)))
        		vars.str = readline("Minishell: ");	
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			vars.str = ft_strtrim(line, "\n");
			free(line);
		}
		after_readline_signals();
        if (vars.str == NULL)
        {
            return (0);
        }
		if (init_cmd(&vars, vars.str))
		{
				result = init_pip(&vars);
		}
	}
	return (vars.last_pid);
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


