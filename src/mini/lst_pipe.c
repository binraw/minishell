/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:31:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/01 11:05:06 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_pip(t_data *data)
{
    int i;

    i = 0;
	command_rdocs(data);
	if (data->number_of_pip == 0)
		data->pip = NULL;
	else
	{
    	data->pip = malloc(data->number_of_pip * sizeof(int*));
		if (!data->pip)
			return (-1);
	}
	data->tab_pid = malloc((data->number_of_cmd) * sizeof(pid_t));
	data->free_pid = false;
	if (!data->tab_pid)
	{
		ft_lstclear_data(data);	
		return (-1);
	}
    while (i < data->number_of_pip)
    {
        data->pip[i] = malloc(2 * sizeof(int));
		if (!data->pip[i])
		{
			ft_lstclear_data(data);
			return (-1);
		}
        i++;
    }
	return (pipex_process_multi(data, data->pip, data->tab_pid));
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
		free_exec_part(data);
		return (result);
	}
	if (loop_process_pipe(data, dup, pip, tab_pid) == -1)
		return (-1);
	result = status_process(data, tab_pid);
	return (result);
}

int	status_process(t_data *data, pid_t *tab_pid)
{
	int result;
	result = process_status_pid(data, tab_pid);
	data->last_pid = result;
	return (result);
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
		// printf("ici\n");
		open_all_redir(dup, data);
		if(get_last_out(dup->redir))
			value_final_out(dup, data);
		else if	(get_last_in(dup->redir))
		{
			value_final_in(dup, data);
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
				result = child_process_multi(data, dup, NULL);
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
	int i;
	int status;
	pid_t wpid;


	if (data->cmd->fd_rdoc != 0)
		close(data->cmd->fd_rdoc);
	status = 0;
	i = 0;
	wpid = 0;
	while (wpid != -1)
	{
		wpid = waitpid(0, &status, 0);
		if (!data->cmd->content[0])
			tab_pid[0] = 0;
		else if(data->number_of_pip == 0 && (control_builtin(data->cmd) == 1))	
			tab_pid[0] = 0;
		if (wpid == tab_pid[data->number_of_pip])  // avant data->number_of_cmd - 1
			data->last_pid = status;
		i++;
	}
	if (WIFEXITED(data->last_pid))
		return(WEXITSTATUS(data->last_pid));
	else if (WIFSIGNALED(data->last_pid) && data->last_pid != 1)
		return(128 +  WTERMSIG(data->last_pid));
	return (data->last_pid);
}



int	child_process_multi(t_data *data, t_node_cmd *cmd, int *pip)
{
	char	*path_command;

	path_command = NULL;
	if ( cmd->content[0][0] == '\0' && !cmd->redir)
	{
		if (pip)
		{
			close(pip[0]);
			close(pip[1]);
		}
		ft_putstr_fd(cmd->content[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_lstclear_data(data);
	 	exit(127);


	}

	if (cmd->content[0] && (control_builtin(cmd) == 0))
		path_command = create_path(cmd->content[0], data->env);
	if (!cmd->content[0])
	{
		ft_putstr_fd("command not found\n", 2);
		ft_lstclear_data(data);
	 	exit(127);
	}
	if ((!path_command && (control_builtin(cmd) == 0)))
	{
		if (pip)
		{
			close(pip[0]);
			close(pip[1]);
		}
		ft_putstr_fd(cmd->content[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_lstclear_data(data);
	 	exit(127);
	}
	if (cmd->redir)
	{
		if (pip)
			ft_redir_child_process(cmd, pip, data);
		else
			ft_redir_child_process_one(cmd, data);
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
	if (cmd->content[0][0] == '\0' && !cmd->redir)
	{
		close(pip[y][0]);
		close(pip[y][1]);
		ft_putstr_fd(cmd->content[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_lstclear_data(data);
	 	exit(127);
	}
	if (!cmd->content[0] && cmd->redir)
	{
		open_all_redir(cmd, data);
		if(get_last_out(cmd->redir))
		{
			value_final_out(cmd, data);
			close(value_final_out(cmd, data));
		}
		else if	(get_last_in(cmd->redir))
		{
			value_final_in(cmd, data);
			return (1);
		}
		return(0);
	}

	if ((cmd) && (control_builtin(cmd) == 0))
		path_command = create_path(cmd->content[0], data->env);
	if ((!path_command && (control_builtin(cmd) == 0)) )
	{
		close(pip[y][0]);
		close(pip[y][1]);
		ft_putstr_fd(cmd->content[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_lstclear_data(data);
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
