/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:37:53 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/09/02 10:48:52 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int	command_cd(t_data *data)
{
	char	*old_pwd;
	char	*new_value;

	new_value = NULL;
	old_pwd = value_pwd(data->env_node);
	if (!old_pwd)
	{
		ft_putstr_fd("error oldpwd", 2);
		ft_lstclear_data(data);
		exit(1);
	}
	if (ft_strncmp(data->cmd->content[0], "cd",
			ft_strlen(data->cmd->content[0])) == 0
		&& !data->cmd->content[1])
		cd_to_home(data);
	else
		return (move_no_at_home(data, new_value, old_pwd));
	free(old_pwd);
	if (new_value)
		free(new_value);
	return (0);
}

void	move_position(t_data *data, char *old_pwd, char *new_value)
{
	char	*content;

	content = ft_strjoin("/", data->cmd->content[1]);
	if (!content)
		free_old_data(data, old_pwd);
	new_value = ft_strjoin(old_pwd, content);
	if (!new_value)
		free_old_data(data, old_pwd);
	if (modify_value(data->env_node, "OLDPWD", old_pwd) == -1)
	{
		free(new_value);
		free(content);
		free_old_data(data, old_pwd);
	}
	if (modify_value(data->env_node, "PWD", new_value) == -1)
	{
		free(new_value);
		free(content);
		free_old_data(data, old_pwd);
	}
	free(new_value);
	free(content);
	free(old_pwd);
}

void	free_old_data(t_data *data, char *old_pwd)
{
	free(old_pwd);
	ft_lstclear_data(data);
	exit(1);
}

char	*value_old_pwd(t_node_env *head)
{
	t_node_env	*current;
	size_t		i;
	char		*value;

	current = head;
	i = 0;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "OLDPWD",
				ft_strlen(current->name + 1)) == 0)
		{
			while (current->content[i] != '=' && current->content[i])
				i++;
			i++;
			value = ft_strdup((current->content + i));
			if (!value)
				return (0);
			return (value);
		}
		current = current->next;
	}
	return (0);
}

int	cd_to_home(t_data *data)
{
	t_node_env	*copy;
	char		*old_pwd;

	old_pwd = value_pwd(data->env_node);
	if (!old_pwd)
	{
		ft_putstr_fd("error oldpwd", 2);
		ft_lstclear_data(data);
		exit(1);
	}
	copy = data->env_node;
	while (copy)
	{
		if (ft_strncmp(copy->name, "HOME", ft_strlen(copy->name)) == 0)
			break ;
		copy = copy->next;
	}
	if (!copy)
		error_copy_env(data, old_pwd);
	if (chdir(copy->value) == 0)
		move_to_home(data, copy, old_pwd);
	free(old_pwd);
	return (0);
}
