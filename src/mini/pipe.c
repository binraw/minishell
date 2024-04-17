/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:58:01 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/17 13:39:12 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int init_pip(t_data *data)
{
    int **pip;
    int i;
    int y;

    i = 0;
    y = 0;
    pip = malloc(data->number_of_pip * sizeof(int*));
    while (i < data->number_of_pip)
    {
        pip[i] = malloc(2 * sizeof(int));
		if (!pip[i])
			return (-1);   //free ceux qui non pas rater
        i++;
    }
    i = 0;
    while (i < data->number_of_pip)
    {
        pipex_process_multi(data, pip[i]);
        i++;
    }
    return (0);
}

int	pipex_process_multi(t_data *data, int *pip)
{
	pid_t	first_child;
	pid_t	second_child;
	int		status;
    int     i;

	status = 0;
    i = 0;
    while (data->number_of_cmd < i)
    {
	first_child = fork();
	if (first_child == -1)
		return (-1);
	if (first_child == 0)
		child_process_multi(data, i, pip);
    i++;
	second_child = fork();
	if (second_child == -1)
		return (-1);
	if (second_child == 0)
		second_child_process_multi(data, i, pip);
	close(pip[0]);
	close(pip[1]);
	waitpid(first_child, &status, 0);
	waitpid(second_child, &status, 0);
    i++;
    }
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	child_process_multi(t_data *data, t_redir *redir, int i, int *pip)
{
	int		filein;
	char	*path_command;

	path_command = NULL;
	if (command)
		path_command = create_path(data->cmd[i], data->env);
	if (!path_command)
		return (-1);
    if (i == 0)
	    dup2(redir->in, STDIN_FILENO);
    else
        dup2(pip[0], STDIN_FILENO);
    if (i == data->number_of_cmd)
    {
        dup2(redir->out, STDOUT_FILENO);
        close(pip[1]);
	    close(pip[0]);
        execve(path_command, data->cmd, data->envp);
	    perror("execve");
	    exit(127);
	    return (0);
    }
	dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
	close(pip[0]);
	execve(path_command, data->cmd, data->envp);
	perror("execve");
	exit(127);
	return (0);
}


int	second_child_process_multi(t_data *data, t_redir *redir, int i, int *pip)
{
	int		fileout;
	char	*path_command;

	path_command = NULL;
	if (command)
		path_command = create_path(data->cmd[i], data->env);
	if (!path_command)
		error_path(command, 3, argv);
	dup2(pip[0], STDIN_FILENO);
    if (i == data->number_of_cmd)
    {
        dup2(redir->out, STDOUT_FILENO);
        close(pip[1]);
	    close(pip[0]);
        execve(path_command, data->cmd, data->envp);
	    perror("execve");
	    exit(127);
	    return (0);
    }
	dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	close(pip[1]);
	execve(path_command, data->cmd, data->env);
	perror("execve");
	exit(127);
	return (0);
}
