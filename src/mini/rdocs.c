/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdocs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:54:57 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/30 10:55:08 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	init_rdocs(t_rdocs *rdocs)
{
	int	*fd;

	setup_readline_rdocs();
	fd = malloc(2 * sizeof(int));
	if (!fd)
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	rdocs->go = false;
	while (rdocs->go != true)
	{
		rdocs->str_rdocs = readline("> ");
		if (!rdocs->str_rdocs)
			return (rdocs_error(fd));
		if (ft_strncmp(rdocs->str_rdocs,
				rdocs->limit, (ft_strlen(rdocs->str_rdocs)) + 1) == 0)
			return (stop_success_rdocs(rdocs, fd));
		if (g_interrupted == 1)
		{
			rdocs_error(fd);
			break ;
		}
		print_rdocs(rdocs, fd);
	}
	return (-1);
}

int	open_all_rdocs(t_node_cmd *cmd)
{
	t_redir	*last_in;
	t_rdocs	*dup;
	int		fd;

	last_in = get_last_in(cmd->redir);
	if (!last_in)
		return (0);
	dup = cmd->rdocs;
	fd = 0;
	while (dup)
	{
		fd = init_rdocs(dup);
		if (fd == -1)
			return (-1);
		dup = dup->next;
	}
	if (last_in->rdocs)
		cmd->fd_rdoc = fd;
	return (0);
}

int	command_rdocs(t_data *data)
{
	t_node_cmd	*dup;

	dup = data->cmd;
	while (dup)
	{
		if (dup->rdocs)
			open_all_rdocs(dup);
		dup = dup->next;
	}
	return (0);
}
