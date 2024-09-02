/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:49:07 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/09/02 10:40:36 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	open_all_redir(t_node_cmd *cmd, t_data *data)
{
	t_redir	*dup;

	dup = cmd->redir;
	while (dup)
	{
		if (dup->in)
			open_redir_in(dup, data);
		else if (dup->out)
			open_redir_out(dup, data);
		else if (dup->d_out)
			open_redir_d_out(dup, data);
		dup = dup->next;
	}
	return (0);
}

int	open_redir_in(t_redir *dup, t_data *data)
{
	int		i;
	t_redir	*last_in;

	last_in = get_last_in(dup);
	i = 0;
	if (dup != last_in)
	{
		i = open(dup->content, O_RDONLY, 00644);
		if (i < 0)
		{
			ft_putstr_fd(dup->content, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			ft_lstclear_data(data);
			exit(1);
		}
		close(i);
	}
	return (0);
}

int	open_redir_out(t_redir *dup, t_data *data)
{
	int		i;
	t_redir	*last_out;

	last_out = get_last_out(dup);
	i = 0;
	if (dup != last_out)
	{
		i = open(dup->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
		if (i < 0)
		{
			ft_lstclear_data(data);
			exit(1);
		}
		close(i);
	}
	return (0);
}

int	open_redir_d_out(t_redir *dup, t_data *data)
{
	int		i;
	t_redir	*last_out;

	last_out = get_last_out(dup);
	i = 0;
	if (dup != last_out)
	{
		i = open(dup->content, (O_CREAT | O_WRONLY | O_APPEND), 00644);
		if (i < 0)
		{
			ft_putstr_fd(dup->content, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			ft_lstclear_data(data);
			exit(1);
		}
		close(i);
	}
	return (0);
}

int	redir_no_cmd(t_data *data, t_node_cmd *dup)
{
	open_all_redir(dup, data);
	if (get_last_out(dup->redir))
		close(value_final_out(dup, data));
	else if (get_last_in(dup->redir))
	{
		value_final_in(dup, data);
		return (0);
	}
	return (0);
}
