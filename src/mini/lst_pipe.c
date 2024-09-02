/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:31:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/09/02 10:34:30 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	init_pip(t_data *data)
{
	if ((!data->cmd->content || !data->cmd->content[0]) && !data->cmd->redir)
		return (0);
	command_rdocs(data);
	if (data->number_of_pip == 0)
		data->pip = NULL;
	else
	{
		data->pip = malloc(data->number_of_cmd * sizeof(int *));
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
	if (process_init_pip(data) == -1)
		return (-1);
	return (pipex_process_multi(data, data->pip, data->tab_pid));
}

int	process_init_pip(t_data *data)
{
	int	i;

	i = 0;
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
	if (data->pip && data->number_of_pip != 0)
		data->pip[i] = NULL;
	return (0);
}

int	status_process(t_data *data, pid_t *tab_pid)
{
	int	result;

	result = process_status_pid(data, tab_pid);
	data->last_pid = result;
	return (result);
}

int	process_status_pid(t_data *data, pid_t *tab_pid)
{
	int		status;
	pid_t	wpid;

	if (data->cmd->fd_rdoc != 0)
		close(data->cmd->fd_rdoc);
	status = 0;
	wpid = 0;
	set_sig_ignore();
	while (wpid != -1)
	{
		wpid = waitpid(0, &status, 0);
		if (!data->cmd->content[0])
			tab_pid[0] = 0;
		else if (data->number_of_pip == 0 && (control_builtin(data->cmd) == 1))
			tab_pid[0] = 0;
		if (wpid == tab_pid[data->number_of_pip])
			data->last_pid = status;
	}
	setup_readline_signals(data);
	return (manage_pid_exit_status(data));
}

int	manage_pid_exit_status(t_data *data)
{
	if (WIFEXITED(data->last_pid))
		return (WEXITSTATUS(data->last_pid));
	else if (WIFSIGNALED(data->last_pid) && data->last_pid != 1)
	{
		if (WTERMSIG(data->last_pid) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		if (WTERMSIG(data->last_pid) == SIGINT)
			write(2, "\n", 1);
		return (128 + WTERMSIG(data->last_pid));
	}
	return (data->last_pid);
}
