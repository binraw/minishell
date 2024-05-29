/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:31:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/29 13:34:38 by rtruvelo         ###   ########.fr       */
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
	int i;
	t_node_cmd *dup;

	y = 0;
	i = 0;
	dup = data->cmd;
	open_all_rdocs(dup);
	if (pipe(pip[y]) == -1)
		return (-1);
	tab_pid[i] = fork();
	if (tab_pid[i] == -1)
		return (-1);	

	if (tab_pid[i] == 0)
		child_process_multi(data, dup, pip[y]);
  	dup = dup->next;
	i++;
    while (i < data->number_of_cmd)
    {
		if ((i + 1) < (data->number_of_cmd))
			if (pipe(pip[y + 1]) == -1)
        		return (-1);
		tab_pid[i] = fork();
		if (tab_pid[i] == -1)
			return (-1);
		if (tab_pid[i] == 0)
			second_child_process_multi(data, dup, pip, y);
		close(pip[y][0]);
		close(pip[y][1]);
		y++;
		i++;
		dup = dup->next;
    }
	process_status_pid(data, tab_pid);
	if (data->last_pid)
		return (WEXITSTATUS(data->last_pid));
	return (0);
}

int	process_status_pid(t_data *data, pid_t *tab_pid)
{
	int		*status;
	t_node_cmd *dup;
	int i;

	dup = data->cmd;
	i = 0;
	status = malloc((data->number_of_cmd) * sizeof(int));
	while (dup)
	{
		waitpid(tab_pid[dup->index], &status[dup->index], 0);
		i++;
		dup = dup->next;
	}
	data->last_pid = status[i - 1]; // ici a voir car je pense pas besoin de garder le -1
	return (data->last_pid);
}

int	child_process_multi(t_data *data, t_node_cmd *cmd, int *pip)
{
	char	*path_command;
	int		y;
	int		i;

	y = -1;
	i = 0; // ici le i est juste provisoire pour voir comment implementer ca
	path_command = NULL;
	if (cmd->content[0])
		path_command = create_path(cmd->content[0], data->env);
	if (!path_command)
		return (-1);
	if (cmd->redir)	
	{
		ft_redir_child_process(data->cmd, pip);
	}
	else
		first_child(pip);	
	execve(path_command, cmd->content, data->env);
	perror("execve");
	exit(127);
	return (0);
}


int	second_child_process_multi(t_data *data, t_node_cmd *cmd, int **pip, int y)
{
	char	*path_command;

	path_command = NULL;
	if (cmd)
		path_command = create_path(cmd->content[0], data->env);
	if (!path_command)
		return(printf("error second child"), -1);
	if (cmd->redir)
	{
		ft_dup_redir_second_child(data, cmd, pip, y);
	}
	else
	{
		second_child(data, pip, y, cmd);
	}
	execve(path_command, cmd->content, data->env);
	perror("execve");
	exit(127);
	return (0);
}
