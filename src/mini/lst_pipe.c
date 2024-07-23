/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:31:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/17 10:06:09 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_pip(t_data *data)
{
    int **pip;
    int i;
	pid_t	*tab_pid;

    i = 0;
	command_rdocs(data);
		
		if (data->number_of_pip == 0)
			pip = NULL;
		else
		{
    		pip = malloc(data->number_of_pip * sizeof(int*));
		 	if (!pip)
		 	return (-1);
		}
		tab_pid = malloc((data->number_of_cmd) * sizeof(pid_t));
		if (!tab_pid)
		{
		// int y;
		// y = data->number_of_pip;
		// 	while (y != 0)
		// 	{	
		// 		if (pip[y])
		// 			free(pip[y]);
		// 		y--;
		// 	}
			free(pip);
			return (-1);
		}
    	while (i < data->number_of_pip)
    	{
        	pip[i] = malloc(2 * sizeof(int));
			if (!pip[i])
				return (-1);
        	i++;
    	}
    	//pipex_process_multi(data, pip, tab_pid); 
	return (pipex_process_multi(data, pip, tab_pid));
}

int	pipex_process_multi(t_data *data, int **pip, pid_t *tab_pid)
{
	t_node_cmd *dup;
	int result;

	dup = data->cmd;
	result = start_process_pipex(data, pip, tab_pid);
  	dup = dup->next;
	if (dup == NULL)
	{
		result = status_process(data, tab_pid);
		// if (result == -1)
		// 	return (-1);
		return (result);
	}
	if (loop_process_pipe(data, dup, pip, tab_pid) == -1)
		return (-1);
	result = status_process(data, tab_pid);
	// printf("valeur de result avant %d \n" , result);
	// if (result == -1)
	// 	return (-1);
	return (result);
}



int	status_process(t_data *data, pid_t *tab_pid)
{
	int result;
	result = process_status_pid(data, tab_pid);
	data->last_pid = result;
	return (data->last_pid);
}


int	start_process_pipex(t_data *data, int **pip, pid_t *tab_pid)
{
	int		y;
	int i;
	t_node_cmd *dup;
	int result;

	y = 0;
	i = 0;
	result = 0;
	dup = data->cmd;
	if (!dup->content[0] && dup->redir)
	{
		open_all_redir(dup);
		if(get_last_out(dup->redir))
			value_final_out(dup);
		else if	(get_last_in(dup->redir))
		{
			value_final_in(dup);
			return (1);
		}
		return(0);
	}
		
	if (data->number_of_pip != 0)
		if (pipe(pip[y]) == -1)
			return (-1);
	if ((data->number_of_cmd == 1) && (control_builtin(dup) == 1) && !dup->redir)
	{
		if (!pip)
			result = road_builtin(data, dup, NULL, y);
		else
			result = road_builtin(data, dup, pip, y);
	}
	else 
	{

		tab_pid[i] = fork();
		if (tab_pid[i] == -1)
			return (-1);	
		if (tab_pid[i] == 0)
		{
			if (!pip)
			{
				result = child_process_multi(data, dup, NULL);
			}
			else
				result = child_process_multi(data, dup, pip[y]);
		}
	}
	return (data->last_pid);
}

int	loop_process_pipe(t_data *data, t_node_cmd *dup, int **pip, pid_t *tab_pid)
{
	int i;
	int y;

	i = 1;
	y = 0;

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
	return (0); 
}


int	process_status_pid(t_data *data, pid_t *tab_pid)
{
	t_node_cmd *dup;
	int i;
	int status;
	pid_t wpid;

	status = 0;
	dup = data->cmd;
	i = 0;
	wpid = 0;
	while (wpid != -1)
	{
		wpid = waitpid(0, &status, 0);
		if (wpid == tab_pid[data->number_of_cmd - 1])
			data->last_pid = status;
		i++;
	}
	if (WIFEXITED(data->last_pid))
	{
		return(WEXITSTATUS(data->last_pid));
	}
	else if (WIFSIGNALED(data->last_pid))
	{
		return(128 +  WTERMSIG(data->last_pid));
	}
	return (data->last_pid);
}



int	child_process_multi(t_data *data, t_node_cmd *cmd, int *pip)
{
	char	*path_command;

	path_command = NULL;
	
	if (cmd->content[0])
	{
		
		path_command = create_path(cmd->content[0], data->env);
	}
	if (!cmd->content[0])
	{
		 printf("command not found\n");
		// data->last_pid = 127;
	 	exit(127);
	}
	if (!path_command && (control_builtin(cmd) == 0))
	{
		// printf("ici\n");
		 printf("%s: command not found\n", cmd->content[0]);
		// data->last_pid = 127;
	 	exit(127);
	}
	
	if (cmd->redir)
	{
		if (pip)
			ft_redir_child_process(cmd, pip);
		else
			ft_redir_child_process_one(cmd);
	}
	else if (pip)
		first_child(pip);

	if ((control_builtin_multi_command(data, cmd, 1) == 0))
	{
		execve(path_command, cmd->content, data->env);
		perror("execve");
	}
	return (0);
}



int	second_child_process_multi(t_data *data, t_node_cmd *cmd, int **pip, int y)
{
	char	*path_command;

	path_command = NULL;
	if ((cmd) && (control_builtin(cmd) == 0))
		path_command = create_path(cmd->content[0], data->env);
	if (!path_command && (control_builtin(cmd) == 0))
	{
		printf("%s: command not found\n", cmd->content[0]);
	 	exit(127);
	}
	if (cmd->redir)
		ft_dup_redir_second_child(data, cmd, pip, y);
	else
		second_child(data, pip, y, cmd);
	if ((control_builtin_multi_command(data, cmd, 1)== 0))
	{
		execve(path_command, cmd->content, data->env);
		perror("execve");
	}
	return (0);
}
