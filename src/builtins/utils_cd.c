/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:22:42 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/09/02 10:49:22 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

void	error_copy_env(t_data *data, char *old_pwd)
{
	ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
	free(old_pwd);
	ft_lstclear_data(data);
	exit(1);
}

void	move_to_home(t_data *data, t_node_env *copy, char *old_pwd)
{
	if (modify_value(data->env_node, "OLDPWD", old_pwd) == -1)
	{
		free(old_pwd);
		ft_lstclear_data(data);
		exit(1);
	}
	if (modify_value(data->env_node, "PWD", copy->value) == -1)
	{
		free(old_pwd);
		ft_lstclear_data(data);
		exit(1);
	}
}

int	move_no_at_home(t_data *data, char *new_value, char *old_pwd)
{
	if (chdir(data->cmd->content[1]) == 0)
	{
		move_position(data, old_pwd, new_value);
		return (0);
	}
	if (data->cmd->content[1])
		new_value = build_new_pos(data, old_pwd);
	if (chdir(new_value) == 0)
		return (change_content_pos(data, old_pwd, new_value), 0);
	else
	{
		print_error_cd(data->cmd);
		free(old_pwd);
		if (new_value)
			free(new_value);
		return (1);
	}
	free(old_pwd);
	if (new_value)
		free(new_value);
	return (0);
}

void	empty_pos(t_data *data)
{
	perror("malloc() error");
	ft_lstclear_data(data);
	exit(1);
}

void	content_data_free(t_data *data, char *content)
{
	if (content)
		free(content);
	ft_lstclear_data(data);
	exit(1);
}
