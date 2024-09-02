/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:29:28 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/26 11:51:28 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int	modify_value(t_node_env *head, char *name, char *newValue)
{
	char	*new_content;
	char	*content;

	new_content = ft_strjoin(name, "=");
	if (!new_content)
		return (-1);
	content = ft_strdup(new_content);
	if (!content)
	{
		free(new_content);
		return (-1);
	}
	free(new_content);
	new_content = ft_strjoin(content, newValue);
	if (!new_content)
	{
		free(content);
		return (-1);
	}
	free(content);
	return (last_step_modify(head, name, new_content));
}

int	last_step_modify(t_node_env *head, char *name, char *new_content)
{
	while (head != NULL)
	{
		if (ft_strncmp(head->name, name, ft_strlen(head->name) + 1) == 0)
		{
			free(head->content);
			head->content = ft_strdup(new_content);
			if (!head->content)
				return (-1);
			free(new_content);
			return (0);
		}
		head = head->next;
	}
	free(new_content);
	return (0);
}

void	change_content_pos(t_data *data, char *old_pwd, char *new_value)
{
	if (modify_value(data->env_node, "OLDPWD", old_pwd) == -1)
		content_data_free(data, NULL);
	if (modify_value(data->env_node, "PWD", new_value) == -1)
		content_data_free(data, NULL);
	free(old_pwd);
	free(new_value);
}

char	*build_new_pos(t_data *data, char *old_pwd)
{
	char	*new_value;
	char	*content;

	new_value = ft_strjoin("/", data->cmd->content[1]);
	if (!new_value)
		content_data_free(data, NULL);
	content = ft_strdup(new_value);
	if (!content)
		content_data_free(data, new_value);
	free(new_value);
	new_value = ft_strjoin(old_pwd, content);
	if (!new_value)
		content_data_free(data, content);
	free(content);
	if (ft_strncmp(data->cmd->content[0], "cd",
			ft_strlen(data->cmd->content[0])) == 0
		&& ft_strncmp(data->cmd->content[1], "..",
			ft_strlen(data->cmd->content[1])) == 0)
		change_old_pwd(data);
	return (new_value);
}

void	change_old_pwd(t_data *data)
{
	char	*old_pwd;

	old_pwd = value_old_pwd(data->env_node);
	if (!old_pwd)
	{
		ft_lstclear_data(data);
		exit(1);
	}
	if (modify_value(data->env_node, "OLDPWD", old_pwd) == -1)
	{
		free(old_pwd);
		ft_lstclear_data(data);
		exit(1);
	}
	if (modify_value(data->env_node, "PWD", old_pwd) == -1)
	{
		free(old_pwd);
		ft_lstclear_data(data);
		exit(1);
	}
	free(old_pwd);
}
