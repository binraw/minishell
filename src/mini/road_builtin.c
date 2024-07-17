/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:16:25 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/17 13:15:12 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mini.h"


int road_builtin(t_data *data, t_node_cmd *cmd, int **pip, int y)
{

		if (cmd->redir)
		{
			if (pip)
				ft_redir_child_process(cmd, pip[y]);
			else
				ft_redir_child_process_one(cmd);

		}
		else if (pip)
			first_child(pip[y]);


	control_builtin_to_command(data, cmd, 1);
	return (0);
}


int	control_builtin_to_command(t_data *data, t_node_cmd *cmd, int pip)
{
	int i;


	i = 0;
		if (ft_strncmp(cmd->content[0], "env", ft_strlen(cmd->content[0])) == 0)
		{
	
			command_env(data, pip);
			return (1);
		}
		if (ft_strncmp(cmd->content[0], "export", ft_strlen(cmd->content[0])) == 0)
		{
			
			if (cmd->content[1])
			{
				add_env_value(data, cmd->content[1]);
			}
			else
			{

		   		while (i < ft_lstsize(data->env_node))
				{
					screen_export(data,  pip);
					i++;
				}
				i = 0;
				reset_print_env(data);
			}

			return (1);
		}
		if (ft_strncmp(cmd->content[0], "unset", ft_strlen(cmd->content[0])) == 0)
		{
			unset_command(data, &cmd->content[1]);
			return (1);
		}
		if (ft_strncmp(cmd->content[0], "pwd", ft_strlen(cmd->content[0])) == 0)
		{
			command_pwd(data, pip);
			return (1);
		}
		if (ft_strncmp(cmd->content[0], "cd", ft_strlen(cmd->content[0])) == 0)
		{
			command_cd(data);
			return (1);
		}
		if (ft_strncmp(cmd->content[0], "echo", ft_strlen(cmd->content[0])) == 0)
		{
			command_echo(data, pip);
			return (1);
		}
		if (ft_strncmp(cmd->content[0], "exit", ft_strlen(cmd->content[0])) == 0)
			return (command_exit(cmd));
	return (0);
}





int	control_builtin_multi_command(t_data *data, t_node_cmd *cmd, int pip)
{
	int i;


	i = 0;
		if (ft_strncmp(cmd->content[0], "env", ft_strlen(cmd->content[0])) == 0)
		{
	
			command_env(data, pip);
			exit(0);
		}
		if (ft_strncmp(cmd->content[0], "export", ft_strlen(cmd->content[0])) == 0)
		{
			
			if (cmd->content[1])
			{
				add_env_value(data, cmd->content[1]);
			}
			else
			{

		   		while (i < ft_lstsize(data->env_node))
				{
					screen_export(data,  pip);
					i++;
				}
				i = 0;
				reset_print_env(data);
			}

			exit(0);
		}
		if (ft_strncmp(cmd->content[0], "unset", ft_strlen(cmd->content[0])) == 0)
		{
			unset_command(data, &cmd->content[1]);
			exit(0);
		}
		if (ft_strncmp(cmd->content[0], "pwd", ft_strlen(cmd->content[0])) == 0)
		{
			command_pwd(data, pip);
			exit(0);
		}
		if (ft_strncmp(cmd->content[0], "cd", ft_strlen(cmd->content[0])) == 0)
		{
			command_cd(data);
			exit(0);
		}
		if (ft_strncmp(cmd->content[0], "echo", ft_strlen(cmd->content[0])) == 0)
		{
			command_echo(data, pip);
			exit(0);
		}
		if (ft_strncmp(cmd->content[0], "exit", ft_strlen(cmd->content[0])) == 0)
			return (command_exit(cmd));
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
