/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:31:34 by rtruvelo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/17 12:51:43 by rtruvelo         ###   ########.fr       */
=======
/*   Updated: 2024/06/05 11:14:56 by rtruvelo         ###   ########.fr       */
>>>>>>> exec
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_pip(t_data *data)
{
    int **pip;
    int i;
	pid_t	*tab_pid;

    i = 0;
<<<<<<< HEAD
	if (data->number_of_pip == 0 && data->number_of_cmd == 1)
	{
		exe_cmd(data);
=======
	command_rdocs(data);
	if (data->number_of_pip == 0 && data->number_of_cmd == 1)
	{
		exe_cmd(data);
		return (0);
>>>>>>> exec
	}
    pip = malloc(data->number_of_pip * sizeof(int*));
	tab_pid = malloc((data->number_of_cmd) * sizeof(pid_t));
	if (!pip)
		return (-1);
<<<<<<< HEAD
=======
	if (!tab_pid)
		return (-1);
>>>>>>> exec
    while (i < data->number_of_pip)
    {
        pip[i] = malloc(2 * sizeof(int));
		if (!pip[i])
			return (-1);
        i++;
    }
    pipex_process_multi(data, pip, tab_pid); // ici peut etre creer directement un autre 
<<<<<<< HEAD
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
	printf(" la valeur de cmd->index : %d\n", data->cmd->index);
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
=======
    return (0);
}





int	pipex_process_multi(t_data *data, int **pip, pid_t *tab_pid)
{
	int		y;
	int i;
	t_node_cmd *dup;
	int result;

	y = 0;
	i = 1;
	dup = data->cmd;
	start_process_pipex(data, pip, tab_pid);
  	dup = dup->next;
	if (loop_process_pipe(data, dup, pip, tab_pid) == -1)
		return (-1);
	result = status_process(data, tab_pid);
	if (result == -1)
		return (-1);
	return (result);
}



int	status_process(t_data *data, pid_t *tab_pid)
{
	int	*status;
	int result;

	status = malloc((data->number_of_cmd) * sizeof(int));
	if (!status)
	{
		perror("malloc");
		return (-1);
	}
	if (process_status_pid(data, tab_pid, status) == -1)
		return (-1);
	result = analyze_process_statuses(data, tab_pid, status);
	free(status);
	return (result);
}


int	start_process_pipex(t_data *data, int **pip, pid_t *tab_pid)
{
	int		y;
	int i;
	t_node_cmd *dup;

	y = 0;
	i = 0;
	dup = data->cmd;
	if (pipe(pip[y]) == -1)
		return (-1);
	tab_pid[i] = fork();
	if (tab_pid[i] == -1)
		return (-1);	

	if (tab_pid[i] == 0)
		child_process_multi(data, dup, pip[y]);
	return (0);
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










int analyze_process_statuses(t_data *data, pid_t *tab_pid, int *status) // fonction a changer 
{
	(void)tab_pid;
	int i;
	int signal;

	i = 0;
	while (i <data->number_of_cmd)
	{
        if (WIFSIGNALED(status[i]))
		{
            signal = WTERMSIG(status[i]);
            return (128 + signal); // Common convention to return 128 + signal number
        }
		else if (WIFEXITED(status[i]) && WEXITSTATUS(status[i]) != 0)
            return WEXITSTATUS(status[i]);
		i++;
    }
    if (WIFEXITED(status[data->number_of_cmd - 1]))
        data->last_pid = WEXITSTATUS(status[data->number_of_cmd - 1]);
	else if (WIFSIGNALED(status[data->number_of_cmd - 1]))
	{
        signal = WTERMSIG(status[data->number_of_cmd - 1]);
        return (128 + signal); // Common convention to return 128 + signal number
    }
    return 0;
}

int	process_status_pid(t_data *data, pid_t *tab_pid, int *status)
{
	t_node_cmd *dup;
	int i;

	dup = data->cmd;
	i = 0;
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
>>>>>>> exec

	y = -1;
	i = 0; // ici le i est juste provisoire pour voir comment implementer ca
	path_command = NULL;
<<<<<<< HEAD
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
=======
	if (cmd->content[0])
		path_command = create_path(cmd->content[0], data->env);
	// if (!path_command)
	// {
	// 	printf("command not found\n");	
	// 	return (-1);
	// }
	if (cmd->redir)
		ft_redir_child_process(cmd, pip);
	else
		first_child(pip);

	if ((control_builtin_to_command(data, cmd, 1) == 0))
	{

		execve(path_command, cmd->content, data->env);
		perror("execve");
	}
>>>>>>> exec
	exit(127);
	return (0);
}


<<<<<<< HEAD
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
		ft_dup_redir_second_child(data, cmd, pip, y);
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
=======
int	control_builtin_to_command(t_data *data, t_node_cmd *cmd, int pip)
{
	int i;


	i = 0;
		if (ft_strncmp(cmd->content[0], "exit", ft_strlen(cmd->content[0])) == 0)
    	{

            free(cmd->content);
			command_exit(0);
			return (1);
    	}
		if (ft_strncmp(cmd->content[0], "env", ft_strlen(cmd->content[0])) == 0)
		{
	
			command_env(data, pip);
			return (1);
		}
		if (ft_strncmp(cmd->content[0], "export", ft_strlen(cmd->content[0])) == 0)
		{

			if (cmd->content[1])
			{
				add_env_value(data, cmd->content[1]);
			}
			else
			{
				while (i < ft_lstsize(data->env_node))
				{
					screen_export(data,  pip);
					i++;
				}
				i = 0;
				reset_print_env(data);
			}

			return (1);
		}
		if (ft_strncmp(cmd->content[0], "unset", ft_strlen(cmd->content[0])) == 0)
		{
			unset_command(data, cmd->content[1]);
			return (1);
		}
		if (ft_strncmp(cmd->content[0], "pwd", ft_strlen(cmd->content[0])) == 0)
		{
		
			command_pwd(data, pip);
			
			return (1);
		}
		if (ft_strncmp(cmd->content[0], "cd", ft_strlen(cmd->content[0])) == 0)
		{
			
			command_cd(data);
			// while (i < ft_lstsize(data->env_node))
			// 	{
			// 		screen_export(data,  pip);
			// 		i++;
			// 	}
			return (1);
		}


	
	return (0);
}












int	second_child_process_multi(t_data *data, t_node_cmd *cmd, int **pip, int y)
{
	char	*path_command;

	path_command = NULL;
	if (cmd)
		path_command = create_path(cmd->content[0], data->env);
	// if (!path_command)
	// {
	// 	printf("command not found\n");
	// 	return(-1);
	// }

	if (cmd->redir)
		ft_dup_redir_second_child(data, cmd, pip, y);
	else
		second_child(data, pip, y, cmd);
	if ((control_builtin_to_command(data, cmd, 1) == 0))
	{
		execve(path_command, cmd->content, data->env);
		perror("execve");
	}
>>>>>>> exec
	exit(127);
	return (0);
}
