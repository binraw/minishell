/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:43:56 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/09/02 10:45:09 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	value_final_in(t_node_cmd *cmd, t_data *data)
{
	int	fd_in;

	fd_in = 0;
	if (get_last_in(cmd->redir) && cmd->fd_rdoc == 0)
	{
		fd_in = open(get_last_in(cmd->redir)->content, (O_RDONLY), 00644);
		if (fd_in <= 0)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd->redir->content, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			ft_lstclear_data(data);
			exit(1);
		}
	}
	else
		fd_in = cmd->fd_rdoc;
	return (fd_in);
}

int	value_final_out(t_node_cmd *cmd, t_data *data)
{
	int	fd_out;

	fd_out = 0;
	if (get_last_out(cmd->redir))
	{
		if (get_last_out(cmd->redir)->d_out)
			fd_out = final_value_add(data, cmd, fd_out);
		else
		{
			fd_out = open(get_last_out(cmd->redir)->content,
					(O_CREAT | O_WRONLY | O_TRUNC), 00644);
			if (fd_out < 0)
			{
				ft_lstclear_data(data);
				exit(1);
			}
		}
	}
	return (fd_out);
}

int	final_value_add(t_data *data, t_node_cmd *cmd, int fd_out)
{
	if (get_last_out(cmd->redir)->d_out)
	{
		fd_out = open(get_last_out(cmd->redir)->content,
				(O_CREAT | O_WRONLY | O_APPEND), 00644);
		if (fd_out < 0)
		{
			ft_lstclear_data(data);
			exit(1);
		}
	}
	return (fd_out);
}
