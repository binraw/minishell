/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:31:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/16 14:18:58 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_pip(t_data *data)
{
    int **pip;
    int i;
	pid_t	*tab_pid;

    i = 0;
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
	int		y;

	y = 0;
	if (pipe(pip[y]) == -1)
		return (-1);
	tab_pid[data->cmd->index] = fork();
	if (tab_pid[data->cmd->index] == -1)
		return (-1);
	if (tab_pid[data->cmd->index] == 0)
		child_process_multi(data, data->cmd, pip[y]);
  	data->cmd = data->cmd->next;
    while (data->number_of_cmd > data->cmd->index)
    {
		if ((data->cmd->index + 1) < (data->number_of_cmd))
			if (pipe(pip[y + 1]) == -1)
        		return (-1);
		tab_pid[data->cmd->index] = fork();
		if (tab_pid[data->cmd->index] == -1)
			return (-1);
		if (tab_pid[data->cmd->index] == 0)
			second_child_process_multi(data, data->cmd, pip, y);
		close(pip[y][0]);
		close(pip[y][1]);
		y++;
		data->cmd = data->cmd->next;
    }
	process_status_pid(data, tab_pid);
	if (data->last_pid)
		return (WEXITSTATUS(data->last_pid));
	return (0);
}

int	process_status_pid(t_data *data, pid_t *tab_pid)
{
	int		*status;
	
	status = malloc((data->number_of_cmd) * sizeof(int));
	while (data->cmd->index < data->number_of_cmd)
	{
		waitpid(tab_pid[data->cmd->index], &status[data->cmd->index], 0);
		data->cmd = data->cmd->next;
	}
	data->last_pid = status[data->cmd->index - 1]; // ici a voir car je pense pas besoin de garder le -1
	return (data->last_pid);
}

int	child_process_multi(t_data *data, t_node_cmd *cmd, int *pip)
{
	char	*path_command;
	char	**cmd_finaly;
	int		y;
	int i;

	y = -1;
	i = 0; // ici le i est juste provisoire pour voir comment implementer ca
	path_command = NULL;
	if (cmd)
		path_command = create_path(cmd->content, data->env);
	if (!path_command)
		return (-1);
	if (cmd->redir[i].out != 0 || cmd->redir[i].in != 0)
		ft_redir_child_process(data->cmd, pip);
	else
		first_child(pip);
	cmd_finaly = malloc(data->number_of_cmd * sizeof(char*));
	if (!cmd_finaly)
		return (-1);
	cmd_finaly[0] = malloc((strlen(cmd->content) + 1) * sizeof(char));
	if (!cmd_finaly[0])
		return (-1);
	while (cmd->content[++y])
		cmd_finaly[0][y] =  cmd->content[y];
	cmd_finaly[0][y] = '\0';
	cmd_finaly[1] = NULL;
	execve(path_command, cmd_finaly, data->env);
	perror("execve");
	exit(127);
	return (0);
}


int	second_child_process_multi(t_data *data, t_node_cmd *cmd, int **pip, int y)
{
	char	*path_command;
	char	**cmd_finaly;
	int		x;

	x = -1;
	path_command = NULL;
	if (cmd)
		path_command = create_path(cmd->content, data->env);
	if (!path_command)
		return(printf("error second child"), -1);
	if (cmd->redir->out != 0 || cmd->redir->in != 0)
		ft_dup_redir_second_child(data , pip, y);
	else
		second_child(data, pip, y);
	cmd_finaly = malloc(data->number_of_cmd * sizeof(char*));
	if (!cmd_finaly)
		return (-1);
	cmd_finaly[0] = malloc((strlen(cmd->content) + 1) * sizeof(char));
	if (!cmd_finaly[0])
		return (-1);
	while (cmd->content[++x])
		cmd_finaly[0][x] =  cmd->content[x];
	cmd_finaly[0][x] = '\0';
	cmd_finaly[1] = NULL;
	execve(path_command, cmd_finaly, data->env);
	perror("execve");
	exit(127);
	return (0);
}
