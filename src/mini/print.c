/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/23 09:47:42 by hbouyssi         ###   ########.fr       */
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
			// printf("rentre dans pip\n");
					init_pip(&vars);
		}
	 } 
	return (0);
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


