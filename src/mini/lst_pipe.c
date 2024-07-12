/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:31:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/25 15:24:46 by rtruvelo         ###   ########.fr       */
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
			return (-1);
    	while (i < data->number_of_pip)
    	{
        	pip[i] = malloc(2 * sizeof(int));
			if (!pip[i])
				return (-1);
        	i++;
    	}
    	pipex_process_multi(data, pip, tab_pid); // ici peut etre creer directement un autre 

	return (0);
}





int	pipex_process_multi(t_data *data, int **pip, pid_t *tab_pid)
{
	t_node_cmd *dup;
	int result;

	dup = data->cmd;
	start_process_pipex(data, pip, tab_pid);
  	dup = dup->next;
	if (dup == NULL)
	{
		result = status_process(data, tab_pid);
		if (result == -1)
			return (-1);
		return (result);
	}
	if (loop_process_pipe(data, dup, pip, tab_pid) == -1)
		return (-1);
	result = status_process(data, tab_pid);
	if (result == -1)
		return (-1);
	return (result);
}



int	status_process(t_data *data, pid_t *tab_pid)
{
	int result;
	result = process_status_pid(data, tab_pid);
	printf("valeur de last-pid : %d\n", result);
	return (0);
}


int	start_process_pipex(t_data *data, int **pip, pid_t *tab_pid)
{
	int		y;
	int i;
	t_node_cmd *dup;

	y = 0;
	i = 0;
	dup = data->cmd;
	if (data->number_of_pip != 0)
		if (pipe(pip[y]) == -1)
			return (-1);
	tab_pid[i] = fork();
	if (tab_pid[i] == -1)
		return (-1);	

	if (tab_pid[i] == 0)
	{
		if (!pip)
			child_process_multi(data, dup, NULL);
		else
			child_process_multi(data, dup, pip[y]);
	}
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
	else if (WIFSIGNALED(status))
	{
		return(128 +  WTERMSIG(status));
	}
	return (0);
}



int	child_process_multi(t_data *data, t_node_cmd *cmd, int *pip)
{
	char	*path_command;


	path_command = NULL;
	if (cmd->content[0])
		path_command = create_path(cmd->content[0], data->env);
	if (!cmd->content[0])
	{
		printf("command not found\n");
	 	exit(127);
	}
	if (!path_command && (control_builtin(cmd) == 0))
	{
		//probleme quand je unset PATH
		printf("valeur cmd->content[0] %s\n", cmd->content[0]);
		printf("valeur d control_builtin : %d\n", control_builtin(cmd));
		printf("command not found\n");
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

	if ((control_builtin_to_command(data, cmd, 1) == 0))
	{

		execve(path_command, cmd->content, data->env);
		perror("execve");
	}
	return (0);
}


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
			return (1);
		}
		if (ft_strncmp(cmd->content[0], "echo", ft_strlen(cmd->content[0])) == 0)
		{
			command_echo(data, pip);
			return (1);
		}


	
	return (0);
}



int	control_builtin(t_node_cmd *cmd)
{
		if (ft_strncmp(cmd->content[0], "exit", ft_strlen(cmd->content[0])) == 0)
			return (1);
		if (ft_strncmp(cmd->content[0], "env", ft_strlen(cmd->content[0])) == 0)
			return (1);
		if (ft_strncmp(cmd->content[0], "export", ft_strlen(cmd->content[0])) == 0)
			return (1);
		if (ft_strncmp(cmd->content[0], "unset", ft_strlen(cmd->content[0])) == 0)
			return (1);
		if (ft_strncmp(cmd->content[0], "pwd", ft_strlen(cmd->content[0])) == 0)
			return (1);
		if (ft_strncmp(cmd->content[0], "cd", ft_strlen(cmd->content[0])) == 0)
			return (1);
		if (ft_strncmp(cmd->content[0], "echo", ft_strlen(cmd->content[0])) == 0)
			return (1);
	return (0);
}








int	second_child_process_multi(t_data *data, t_node_cmd *cmd, int **pip, int y)
{
	char	*path_command;

	path_command = NULL;
	if (cmd)
		path_command = create_path(cmd->content[0], data->env);
	if (!path_command && (control_builtin(cmd) == 0))
	{
		printf("command not found\n");
	 	exit(127);
	}
	if (cmd->redir)
		ft_dup_redir_second_child(data, cmd, pip, y);
	else
		second_child(data, pip, y, cmd);
	if ((control_builtin_to_command(data, cmd, 1) == 0))
	{
		execve(path_command, cmd->content, data->env);
		perror("execve");
	}
	return (0);
}
