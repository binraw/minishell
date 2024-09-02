/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:32:56 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/09/02 11:48:53 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	start_process_pipex(t_data *data, int **pip, pid_t *tab_pid)
{
	int			y;
	int			i;
	t_node_cmd	*dup;

	y = 0;
	i = 0;
	dup = data->cmd;
	if (!dup->content[0] && dup->redir)
		return (redir_no_cmd(data, dup));
	if (data->number_of_pip != 0)
		if (pipe(pip[y]) == -1)
			return (-1);
	if ((data->number_of_cmd == 1) && (control_builtin(dup) == 1)
		&& !dup->redir)
	{
		if (!pip)
			road_builtin(data, dup, NULL, y);
		else
			road_builtin(data, dup, pip, y);
	}
	else
		start_child_process(data, dup, tab_pid);
	return (data->last_pid);
}

int	start_child_process(t_data *data, t_node_cmd *dup, pid_t *tab_pid)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	tab_pid[i] = fork();
	if (tab_pid[i] == -1)
		return (-1);
	if (tab_pid[i] == 0)
	{
		set_sigquit_process();
		if (!data->pip)
			child_process_multi(data, dup, NULL);
		else
			child_process_multi(data, dup, data->pip[y]);
	}
	return (0);
}

int	pipex_process_multi(t_data *data, int **pip, pid_t *tab_pid)
{
	t_node_cmd	*dup;
	int			result;

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

int	child_process_multi(t_data *data, t_node_cmd *cmd, int *pip)
{
	char	*path_command;

	path_command = NULL;
	if (cmd->content[0][0] == '\0' && !cmd->redir)
		no_found_command(data, cmd, pip);
	if (cmd->content[0] && (control_builtin(cmd) == 0))
		path_command = create_path(cmd->content[0], data->env);
	if (!cmd->content[0])
		no_found_command(data, cmd, pip);
	if ((!path_command && (control_builtin(cmd) == 0)))
		no_found_command(data, cmd, pip);
	check_status_file(data, cmd, path_command);
	if (cmd->redir)
		process_redir_child_one(data, cmd, pip);
	else if (pip)
		first_child(pip);
	if ((control_builtin_multi_command(data, cmd, 1) == 0))
	{
		execve(path_command, cmd->content, data->env);
		ft_lstclear_data(data);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	loop_process_pipe(t_data *data, t_node_cmd *dup, int **pip, pid_t *tab_pid)
{
	int	i;
	int	y;

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
