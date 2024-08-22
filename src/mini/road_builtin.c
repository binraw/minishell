/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:16:25 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/25 13:29:56 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	road_builtin(t_data *data, t_node_cmd *cmd, int **pip, int y)
{
	if (cmd->redir)
	{
		if (pip)
			ft_redir_child_process(cmd, pip[y], data);
		else
			ft_redir_child_process_one(cmd, data);
	}
	else if (pip)
		first_child(pip[y]);
	control_builtin_to_command(data, cmd, 1);
	return (0);
}

int	control_builtin_to_command(t_data *data, t_node_cmd *cmd, int pip)
{
	if (ft_strncmp(cmd->content[0], "env", ft_strlen(cmd->content[0]) + 1) == 0)
		return (command_env(data, pip));
	if (ft_strncmp(cmd->content[0], "export",
			ft_strlen(cmd->content[0]) + 1) == 0)
		export_process(data, cmd, pip);
	if (ft_strncmp(cmd->content[0], "unset",
			ft_strlen(cmd->content[0]) + 1) == 0)
	{
		unset_command(data, &cmd->content[1]);
		return (1);
	}
	if (ft_strncmp(cmd->content[0], "pwd", ft_strlen(cmd->content[0]) + 1) == 0)
		return (command_pwd(data, pip));
	if (ft_strncmp(cmd->content[0], "cd", ft_strlen(cmd->content[0]) + 1) == 0)
		return (cd_process(data));
	if (ft_strncmp(cmd->content[0], "echo",
			ft_strlen(cmd->content[0]) + 1) == 0)
	{
		command_echo(cmd, pip);
		return (1);
	}
	if (ft_strncmp(cmd->content[0], "exit",
			ft_strlen(cmd->content[0]) + 1) == 0)
		return (command_exit_free(data, cmd));
	return (0);
}

int	control_builtin_multi_command(t_data *data, t_node_cmd *cmd, int pip)
{
	if (ft_strncmp(cmd->content[0], "env", ft_strlen(cmd->content[0]) + 1) == 0)
		env_process_child(data, pip);
	if (ft_strncmp(cmd->content[0], "export",
			ft_strlen(cmd->content[0]) + 1) == 0)
		export_process_child(data, cmd, pip);
	if (ft_strncmp(cmd->content[0], "unset",
			ft_strlen(cmd->content[0]) + 1) == 0)
	{
		unset_command(data, &cmd->content[1]);
		ft_lstclear_data(data);
		exit(0);
	}
	if (ft_strncmp(cmd->content[0], "pwd", ft_strlen(cmd->content[0]) + 1) == 0)
		pwd_process_child(data, pip);
	if (ft_strncmp(cmd->content[0], "cd", ft_strlen(cmd->content[0]) + 1) == 0)
		cd_process_child(data, cmd);
	if (ft_strncmp(cmd->content[0], "echo",
			ft_strlen(cmd->content[0]) + 1) == 0)
		process_echo(data, cmd, pip);
	if (ft_strncmp(cmd->content[0], "exit",
			ft_strlen(cmd->content[0]) + 1) == 0)
		return (command_exit_free(data, cmd));
	return (0);
}

int	control_builtin(t_node_cmd *cmd)
{
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
	if (ft_strncmp(cmd->content[0], "exit", ft_strlen(cmd->content[0])) == 0)
		return (1);
	return (0);
}
