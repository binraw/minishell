/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/05 15:48:21 by rtruvelo         ###   ########.fr       */
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
	int i;

	i = 0;
	init_node_env(&vars, envp);

	while (1)
	{
		init_env(&vars);	
		setup_readline_signals();
        vars.str = readline("Minishell: ");	
	
		after_readline_signals();
        if (vars.str == NULL)
        {
            /*printf("Error input.\n");*/
            return (0);
        }
    
		if (ft_strncmp(vars.str, "exit", ft_strlen(vars.str)) == 0)
    	{
            free(vars.str);
			command_exit(0);
			// command_exit(ft_atoi(argv[1])); la commande finale va ressembler a ca a voir comment on recup les 2 arguments
    	}
		if (ft_strncmp(vars.str, "env", ft_strlen(vars.str)) == 0)
		{
			command_env(&vars);
			exit (0);
		}
		if (ft_strncmp(vars.str, "export", ft_strlen(vars.str)) == 0)
		{
			while (i < ft_lstsize(vars.env_node))
			{
				screen_export(&vars, 1);
				i++;
			}
			i = 0;
			reset_print_env(&vars);
			// exit (0);
		}

		init_cmd(&vars, vars.str);
		init_pip(&vars);

	} 

	return (0);
}

int	exe_cmd(t_data *data)
{
	char	*path_command;
	t_node_cmd	*dup;
	pid_t	pid;
	int status;


	dup = data->cmd;

	if (!data->str)
		return (0);

	
	path_command = create_path(data->cmd->content[0], data->env);
	if (!path_command)
	{
		// faire un truc pour quand c'est un fichier
		return (printf("error command\n"), -1);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0) 
	{
		if (data->cmd->redir)
		{
			ft_redir_one_process(dup);
		}
		execve(path_command, data->cmd->content, data->env);
		perror("execve");
		return (1);
	}
	else 
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			// perror("waitpid");
			return (-1);
		}
		if (WIFEXITED(status))
		{

			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
        	int signal = WTERMSIG(status);
        	// fprintf(stderr, "Last process terminated by signal %d\n", signal);
        	return (128 + signal);
		}
		return (-1);
	}
}


/*char	**init_cmd(char *argv)*/
/*{*/
/*	char	**cmd;*/
/*	int		y;*/
/**/
/*	y = 0;*/
/*	if (argv[y] == '\0')*/
/*		return (NULL);*/
/*	while (argv[y] == ' ')*/
/*	{*/
/*		if (argv[y + 1] == '\0')*/
/*			return (NULL);*/
/*		y++;*/
/*	}*/
/*	cmd = ft_split(argv, ' ');*/
/*	return (cmd);*/
/*}*/



