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
	int fd[2];

	fd[0] = 0;
	fd[1] = 1;
	dup = data->cmd;
	if (!data->str)
		return (0);
	path_command = create_path(dup->content[0], data->env);
	// if (!path_command)
	// {
	// 	// faire un truc pour quand c'est un fichier
	// 	printf("%s\n", data->cmd->content[0]);
	// 	return (printf("error command\n"), -1);
	// } TROUVEZ COMMENT CHECK CA SANS QUE LES BUILTINS BLOQUE CAR ILS NE SONT PAS dasn le chemin de base
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0) 
	{
		if (data->cmd->redir)
			ft_redir_one_process(dup);
	if ((control_builtin_to_command(data, data->cmd, fd[1]) == 0))
	{
		execve(path_command, data->cmd->content, data->env);
		perror("execve");
	}
	close(fd[0]);
	close(fd[1]);
	return (1);
	}
	else 
		return(status_one_cmd(pid));
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
        	// fprintf(stderr, "Last process terminated by signal %d\n", signal);
        return (128 + signal);
	}
	return (-1);
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



