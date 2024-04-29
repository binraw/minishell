/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:58:01 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/29 09:53:56 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
	tab_pid = malloc((data->number_of_cmd) * sizeof(pid_t));
	if (!pip)
		return (-1);
    while (i < data->number_of_pip)
    {
        pip[i] = malloc(2 * sizeof(int));
		if (!pip[i])
			return (-1);
        i++;
    }
    pipex_process_multi(data, pip, tab_pid); // ici peut etre creer directement un autre 
	//chemin si dans un cas il y a une redirection dans une des commandes
    return (0);
}

int	pipex_process_multi(t_data *data, int **pip, pid_t *tab_pid)
{
    int     i;
	int		y;

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
			if (pipe(pip[y + 1]) == -1)
        		return (-1);
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
	int	i;
	int		*status;
	
	i = 0;
	status = malloc((data->number_of_cmd) * sizeof(int));
	while (i < data->number_of_cmd)
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

	y = -1;
	path_command = NULL;
	if (data->cmd)
		path_command = create_path(data->cmd[i], data->env);
	if (!path_command)
		return (-1);
	if (data->redir[i].out != 0 || data->redir[i].in != 0)
		ft_redir_child_process(data, pip, i);
	else
		first_child(pip);
	cmd_finaly = malloc(data->number_of_cmd * sizeof(char*));
	if (!cmd_finaly)
		return (-1);
	cmd_finaly[0] = malloc((strlen(data->cmd[i]) + 1) * sizeof(char));
	if (!cmd_finaly[0])
		return (-1);
	while (data->cmd[i][++y])
		cmd_finaly[0][y] =  data->cmd[i][y];
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

	x = -1;
	path_command = NULL;
	if (data->cmd)
		path_command = create_path(data->cmd[i], data->env);
	if (!path_command)
		return(printf("error second child"), -1);
	if (data->redir->out != 0 || data->redir->in != 0)
		ft_dup_redir_second_child(data , pip, y , i);
	else
		second_child(data, i, pip, y);
	cmd_finaly = malloc(data->number_of_cmd * sizeof(char*));
	if (!cmd_finaly)
		return (-1);
	cmd_finaly[0] = malloc((strlen(data->cmd[i]) + 1) * sizeof(char));
	if (!cmd_finaly[0])
		return (-1);
	while (data->cmd[i][++x])
		cmd_finaly[0][x] =  data->cmd[i][x];
	cmd_finaly[0][x] = '\0';
	cmd_finaly[1] = NULL;
	execve(path_command, cmd_finaly, data->env);
	perror("execve");
	exit(127);
	return (0);
}



