/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:26 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/24 09:27:02 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_dup_redir_second_child(t_data *data, t_node_cmd *cmd, int **pip, int y)
{
	int	fd_in;
	int	fd_out;

	if (open_all_redir(cmd, data) == -1)
		return (-1);
	fd_in = value_final_in(cmd, data);
	fd_out = value_final_out(cmd, data);
	if (2 != data->number_of_cmd && cmd->index != data->number_of_cmd
		&& get_last_in(cmd->redir) && !(get_last_out(cmd->redir)))
		redir_in_to_pipe(pip, y, fd_in);
	else if (2 != data->number_of_cmd && cmd->index
		!= (data->number_of_cmd -1) && get_last_in(cmd->redir)
		&& get_last_out(cmd->redir))
		redir_in_out_to_pipe(pip, y, fd_in, fd_out);
	else if (2 != data->number_of_cmd && cmd->index
		!= (data->number_of_cmd -1) && !(get_last_in(cmd->redir))
		&& get_last_out(cmd->redir))
		redir_out_to_pipe(pip, y, fd_out);
	else
		redir_in_or_out(cmd, pip, y, data);
	return (0);
}

void	redir_in_to_pipe(int **pip, int y, int fd_in)
{
	close(pip[y][1]);
	dup2(fd_in, STDIN_FILENO);
	close(pip[y][0]);
	dup2(pip[y + 1][1], STDOUT_FILENO);
	close(pip[y + 1][1]);
	close(pip[y + 1][0]);
	close(fd_in);
}

void	redir_in_out_to_pipe(int **pip, int y, int fd_in, int fd_out)
{
	close(pip[y][1]);
	dup2(fd_in, STDIN_FILENO);
	close(pip[y][0]);
	dup2(fd_out, STDOUT_FILENO);
	close(pip[y + 1][1]);
	close(pip[y + 1][0]);
	close(fd_in);
	close(fd_out);
}

void	redir_out_to_pipe(int **pip, int y, int fd_out)
{
	close(pip[y][1]);
	dup2(pip[y][0], STDIN_FILENO);
	close(pip[y][0]);
	dup2(fd_out, STDOUT_FILENO);
	close(pip[y + 1][1]);
	close(pip[y + 1][0]);
	close(fd_out);
}

void	redir_in_or_out(t_node_cmd *cmd, int **pip, int y, t_data *data)
{
	if (get_last_in(cmd->redir))
	{
		dup2(value_final_in(cmd, data), STDIN_FILENO);
		close(value_final_in(cmd, data));
	}
	else
		dup2(pip[y][0], STDIN_FILENO);
	if (get_last_out(cmd->redir))
	{
		dup2(value_final_out(cmd, data), STDOUT_FILENO);
		close(value_final_out(cmd, data));
	}
	close(pip[y][0]);
	close(pip[y][1]);
}
