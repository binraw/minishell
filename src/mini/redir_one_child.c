/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_one_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:45:52 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/26 10:40:17 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_redir_child_process_one(t_node_cmd *cmd, t_data *data)
{
	int	fd_out;
	int	fd_in;

	if (open_all_redir(cmd, data) == -1)
		return (-1);
	fd_in = value_final_in(cmd, data);
	fd_out = value_final_out(cmd, data);
	if (!(get_last_in(cmd->redir)) && get_last_out(cmd->redir))
	{
		fd_out = value_final_out(cmd, data);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (get_last_in(cmd->redir) && !(get_last_out(cmd->redir)))
	{
		fd_in = value_final_in(cmd, data);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
		redir_one_in_out_alone(fd_in, fd_out);
	return (0);
}

void	redir_one_in_out(int fd_in, int fd_out, int *fd)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_in);
	close(fd_out);
}

void	redir_one_in_out_alone(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

int	redir_out_first_child(t_data *data, t_node_cmd *cmd, int *pip, int fd_out)
{
	fd_out = value_final_out(cmd, data);
	close(pip[0]);
	dup2(fd_out, STDOUT_FILENO);
	close(pip[1]);
	close(fd_out);
	return (0);
}

int	ft_redir_child_process(t_node_cmd *cmd, int *pip, t_data *data)
{
	int	fd_out;
	int	fd_in;

	if (open_all_redir(cmd, data) == -1)
		return (-1);
	fd_in = value_final_in(cmd, data);
	fd_out = value_final_out(cmd, data);
	if (!(get_last_in(cmd->redir)) && get_last_out(cmd->redir))
		redir_out_first_child(data, cmd, pip, fd_out);
	else if (get_last_in(cmd->redir) && !(get_last_out(cmd->redir)))
	{
		fd_in = value_final_in(cmd, data);
		close(pip[0]);
		dup2(fd_in, STDIN_FILENO);
		dup2(pip[1], STDOUT_FILENO);
		close(pip[1]);
		close(fd_in);
	}
	else
		redir_one_in_out(fd_in, fd_out, pip);
	return (0);
}
