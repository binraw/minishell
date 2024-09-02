/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:39:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/26 10:36:31 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	process_redir_child_one(t_data *data, t_node_cmd *cmd, int *pip)
{
	if (pip)
		ft_redir_child_process(cmd, pip, data);
	else
		ft_redir_child_process_one(cmd, data);
	return (0);
}

void	no_found_command(t_data *data, t_node_cmd *cmd, int *pip)
{
	if (pip)
	{
		close(pip[0]);
		close(pip[1]);
	}
	ft_putstr_fd(cmd->content[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_lstclear_data(data);
	exit(127);
}

int	second_child_process_multi(t_data *data, t_node_cmd *cmd, int **pip, int y)
{
	char	*path_command;

	path_command = NULL;
	if (!cmd->content[0] && !cmd->redir)
		no_found_multi_command(data, cmd, pip, y);
	if (!cmd->content[0] && cmd->redir)
		open_redir_no_cmd_multi(data, cmd);
	if ((cmd) && (control_builtin(cmd) == 0))
		path_command = create_path(cmd->content[0], data->env);
	if ((!path_command && (control_builtin(cmd) == 0)))
		no_found_multi_command(data, cmd, pip, y);
	if (cmd->redir)
		ft_dup_redir_second_child(data, cmd, pip, y);
	else
		second_child(data, pip, y, cmd);
	if ((control_builtin_multi_command(data, cmd, 1) == 0))
	{
		execve(path_command, cmd->content, data->env);
		perror("execve");
	}
	return (0);
}

void	no_found_multi_command(t_data *data, t_node_cmd *cmd, int **pip, int y)
{
	close(pip[y][0]);
	close(pip[y][1]);
	ft_putstr_fd(cmd->content[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_lstclear_data(data);
	exit(127);
}

void	open_redir_no_cmd_multi(t_data *data, t_node_cmd *cmd)
{
	open_all_redir(cmd, data);
	if (get_last_out(cmd->redir))
		close(value_final_out(cmd, data));
	else if (get_last_in(cmd->redir))
		close(value_final_in(cmd, data));
	ft_lstclear_data(data);
	exit(0);
}
