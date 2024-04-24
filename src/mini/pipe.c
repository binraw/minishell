/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:58:01 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/24 11:49:00 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


// int init_pip(t_data *data, t_redir *redir)
// {
//     int **pip;
//     int i;
//     int y;

//     i = 0;
//     y = 0;
// 	if (data->number_of_pip == 0 && data->number_of_cmd == 1)
// 	{
// 		exe_cmd(data);
// 	}
//     pip = malloc(data->number_of_pip * sizeof(int*));
//     while (i < data->number_of_pip)
//     {
//         pip[i] = malloc(2 * sizeof(int));
// 		if (!pip[i])
// 			return (-1);   //free ceux qui non pas rater
//         i++;
//     }
//     i = 0;
//     while (i <= data->number_of_pip)
//     {
//         pipex_process_multi(data, redir, pip[i]);
//         i++;
//     }
//     return (0);
// }

// int	pipex_process_multi(t_data *data, t_redir *redir, int *pip)
// {
// 	pid_t	first_child;
// 	pid_t	second_child;
// 	int		status;
//     int     i;

// 	status = 0;
//     i = 0;
//     while (data->number_of_cmd < i)
//     {
// 	first_child = fork();
// 	if (first_child == -1)
// 		return (-1);
// 	if (first_child == 0)
// 		child_process_multi(data, redir, i, pip);
//     i++;
// 	second_child = fork();
// 	if (second_child == -1)
// 		return (-1);
// 	if (second_child == 0)
// 		second_child_process_multi(data, redir, i, pip);
// 	close(pip[0]);
// 	close(pip[1]);
// 	waitpid(first_child, &status, 0);
// 	waitpid(second_child, &status, 0);
//     i++;
//     }
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (0);
// }

// int	child_process_multi(t_data *data, t_redir *redir, int i, int *pip)
// {
// 	char	*path_command;

// 	path_command = NULL;
// 	if (data->cmd)
// 		path_command = create_path(data->cmd[i], data->env);
// 	if (!path_command)
// 		return (-1);
//     if (i == 0)
// 	    dup2(redir->in, STDIN_FILENO);
//     else
//         dup2(pip[0], STDIN_FILENO);
//     if (i == data->number_of_cmd)
//     {
//         dup2(redir->out, STDOUT_FILENO);
//         close(pip[1]);
// 	    close(pip[0]);
//         execve(path_command, data->cmd, data->env);
// 	    perror("execve");
// 	    exit(127);
// 	    return (0);
//     }
// 	dup2(pip[1], STDOUT_FILENO);
// 	close(pip[1]);
// 	close(pip[0]);
// 	execve(path_command, data->cmd, data->env);
// 	perror("execve");
// 	exit(127);
// 	return (0);
// }


// int	second_child_process_multi(t_data *data, t_redir *redir, int i, int *pip)
// {
// 	char	*path_command;

// 	path_command = NULL;
// 	if (data->cmd)
// 		path_command = create_path(data->cmd[i], data->env);
// 	if (!path_command)
// 		return(printf("error second chil"), -1);
// 	dup2(pip[0], STDIN_FILENO);
//     if (i == data->number_of_cmd)
//     {
//         dup2(redir->out, STDOUT_FILENO);
//         close(pip[1]);
// 	    close(pip[0]);
//         execve(path_command, data->cmd, data->env);
// 	    perror("execve");
// 	    exit(127);
// 	    return (0);
//     }
// 	dup2(pip[1], STDOUT_FILENO);
// 	close(pip[0]);
// 	close(pip[1]);
// 	execve(path_command, data->cmd, data->env);
// 	perror("execve");
// 	exit(127);
// 	return (0);
// }


int init_pip(t_data *data)
{
    int **pip;
    int i;
    int y;
	pid_t	*tab_pid;

    i = 0;
    y = 0;
	if (data->number_of_pip == 0 && data->number_of_cmd == 1)
	{
		exe_cmd(data);
	}
    pip = malloc(data->number_of_pip * sizeof(int*));
	tab_pid = malloc((data->number_of_cmd - 1) * sizeof(pid_t));
	if (!pip)
		return (-1);
    while (i < data->number_of_pip)
    {
        pip[i] = malloc(2 * sizeof(int));
		if (!pip[i])
			return (-1);
        i++;
    }
        pipex_process_multi(data, pip, tab_pid);
    return (0);
}

int	pipex_process_multi(t_data *data, int **pip, pid_t *tab_pid)
{
	int		status;
	int		status_second;
    int     i;
	int		y;

	status = 0;
	status_second = 0;
    i = 0;
	y = 0;
	if (pipe(pip[y]) == -1)
		return (-1);
	tab_pid[i] = fork();
	if (tab_pid[i] == -1)
		return (-1);
	if (tab_pid[i] == 0)
		child_process_multi(data, i, pip[y]);
    i++;
    while (data->number_of_cmd > i)
    {
		if ((i + 1) < (data->number_of_cmd))
		{
			if (pipe(pip[y + 1]) == -1)
        		return (-1);
		}
		tab_pid[i] = fork();
		if (tab_pid[i] == -1)
			return (-1);
		if (tab_pid[i] == 0)
			second_child_process_multi(data, i, pip, y);
		close(pip[y][0]);
		close(pip[y][1]);
		y++;
		i++;
    }
	process_status_pid(data, tab_pid);
	if (data->last_pid)
		return (WEXITSTATUS(data->last_pid));
	return (0);
}

int	process_status_pid(t_data *data, pid_t *tab_pid)
{
	size_t	i;
	int *status;
	
	i = 0;
	status = malloc((data->number_of_cmd - 1) * sizeof(int));
	while (tab_pid[i])
	{
		waitpid(tab_pid[i], &status[i], 0);
		i++;
	}
	data->last_pid = status[i - 1];
	return (data->last_pid);
}

int	child_process_multi(t_data *data, int i, int *pip)
{
	char	*path_command;
	char	**cmd_finaly;
	int		y;

	y = 0;
	path_command = NULL;
	if (data->cmd)
	{
		if (data->cmd[i][0] == '|')
			i++;
		path_command = create_path(data->cmd[i], data->env);
	}
	if (!path_command)
		return (-1);
	close(pip[0]);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
	cmd_finaly = malloc(data->number_of_cmd * sizeof(char*));
	if (!cmd_finaly)
		return (-1);
	cmd_finaly[0] = malloc((strlen(data->cmd[i]) + 1) * sizeof(char));
	if (!cmd_finaly[0])
		return (-1);
	while (data->cmd[i][y])
	{
		cmd_finaly[0][y] =  data->cmd[i][y];
		y++;
	}
	cmd_finaly[0][y] = '\0';
	cmd_finaly[1] = NULL;
	execve(path_command, cmd_finaly, data->env);
	perror("execve");
	exit(127);
	return (0);
}


int	second_child_process_multi(t_data *data, int i, int **pip, int y)
{
	char	*path_command;
	char	**cmd_finaly;
	int		x;
	
	x = 0;
	path_command = NULL;
	if (data->cmd)
		path_command = create_path(data->cmd[i], data->env);
	if (!path_command)
		return(printf("error second child"), -1);
	if (2 != data->number_of_cmd && i != (data->number_of_cmd -1)) // le 2 cest pour eviter quand i y a eulemnt deux commqnde de rentrer dedans
	{
		close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		close(pip[y][0]);
		dup2(pip[y + 1][1], STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
	}
	else
	{
		close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		close(pip[y][0]);
	}
	cmd_finaly = malloc(data->number_of_cmd * sizeof(char*));
	if (!cmd_finaly)
		return (-1);
	cmd_finaly[0] = malloc((strlen(data->cmd[i]) + 1) * sizeof(char));
	if (!cmd_finaly[0])
		return (-1);
	while (data->cmd[i][x])
	{
		cmd_finaly[0][x] =  data->cmd[i][x];
		x++;
	}
	cmd_finaly[0][x] = '\0';
	cmd_finaly[1] = NULL;
	execve(path_command, cmd_finaly, data->env);
	perror("execve");
	exit(127);
	return (0);
}
