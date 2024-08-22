// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   process_builtins.c                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/22 12:42:31 by rtruvelo          #+#    #+#             //
//   Updated: 2024/08/22 12:54:07 by rtruvelo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "mini.h"

int	export_process(t_data *data, t_node_cmd *cmd, int pip)
{
	int	i;

	i = 0;
	if (cmd->content[1])
	{
		if (data->number_of_cmd > 1)
			return (1);
		i = 1;
		while (cmd->content[i])
		{
			add_env_value(data, cmd->content[i]);
			i++;
		}
	}
	else
	{
		while (i < ft_lstsize(data->env_node))
		{
			screen_export(data, pip);
			i++;
		}
		reset_print_env(data);
	}
	return (1);
}

int	cd_process(t_data *data)
{
	if (data->number_of_cmd > 1)
		return (1);
	data->last_pid = command_cd(data);
	return (1);
}

void	process_echo(t_data *data, t_node_cmd *cmd, int pip)
{
	command_echo(cmd, pip);
	ft_lstclear_data(data);
	exit(0);
}

void	export_process_child(t_data *data, t_node_cmd *cmd, int pip)
{
	int	i;

	i = 0;
	if (cmd->content[1])
		add_env_value(data, cmd->content[1]);
	else
	{
		while (i < ft_lstsize(data->env_node))
		{
			screen_export(data, pip);
			i++;
		}
		reset_print_env(data);
	}
	ft_lstclear_data(data);
	exit(0);
}

void	cd_process_child(t_data *data, t_node_cmd *cmd)
{
	if (data->number_of_cmd > 1)
	{
		if (chdir(cmd->content[1]) == 0)
		{
			ft_lstclear_data(data);
			exit(0);
		}
		else
		{
			print_error_cd(cmd);
			ft_lstclear_data(data);
			exit(0);
		}
	}
	command_cd(data);
	ft_lstclear_data(data);
	exit(0);
}
