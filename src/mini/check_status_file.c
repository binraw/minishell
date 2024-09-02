/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:55:39 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/09/02 11:07:04 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	check_status_file(t_data *data, t_node_cmd *cmd)
{
	struct stat	file_stat;

	if (stat(cmd->content[0], &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd(cmd->content[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			open_all_redir(cmd, data);
			ft_lstclear_data(data);
			exit(126);
		}
		else if (S_ISREG(file_stat.st_mode))
		{
			if (!(file_stat.st_mode & S_IXUSR))
			{
				ft_putstr_fd(cmd->content[0], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				open_all_redir(cmd, data);
				ft_lstclear_data(data);
				exit(126);
			}
		}
	}
}
