/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:49:40 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/30 09:42:31 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int	command_pwd(t_data *data, int fd)
{
	char	*pos;
	long	size;

	size = 20;
	while (1)
	{
		pos = malloc((size_t)size * sizeof(char *));
		if (!pos)
			empty_pos(data);
		if (getcwd(pos, (size_t)size) != NULL)
		{
			ft_putstr_fd(pos, fd);
			ft_putchar_fd('\n', fd);
			free(pos);
			break ;
		}
		else
		{
			free(pos);
			size += size;
		}
	}
	return (1);
}

void	empty_pos(t_data *data)
{
	perror("malloc() error");
	ft_lstclear_data(data);
	exit(1);
}

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

void	content_data_free(t_data *data, char *content)
{
	if (content)
		free(content);
	ft_lstclear_data(data);
	exit(1);
}

void	move_position(t_data *data, char *old_pwd, char *new_value)
{
	char	*content;

	content = ft_strjoin("/", data->cmd->content[1]);
	new_value = ft_strjoin(old_pwd, content);
	if (modify_value(data->env_node, "OLDPWD", old_pwd) == -1)
	{
		free(new_value);
		free(content);
		free(old_pwd);
		ft_lstclear_data(data);
		exit(1);
	}
	if (modify_value(data->env_node, "PWD", new_value) == -1)
	{
		free(new_value);
		free(content);
		free(old_pwd);
		ft_lstclear_data(data);
		exit(1);
	}
	free(new_value);
	free(content);
	free(old_pwd);
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
		if (strcmp(head->name, name) == 0)
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

char	*value_old_pwd(t_node_env *head)
{
	t_node_env	*current;
	size_t		i;
	char		*value;

	current = head;
	i = 0;
	while (current != NULL)
	{
		if (strcmp(current->name, "OLDPWD") == 0)
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

char	*value_pwd(t_node_env *head)
{
	t_node_env	*current;
	size_t		i;
	char		*value;

	i = 0;
	current = head;
	while (current != NULL)
	{
		if (strcmp(current->name, "PWD") == 0)
		{
			while (current->content[i] != '=' && current->content[i])
				i++;
			i++;
			value = ft_strdup((current->content + i));
			if (!value)
				return (NULL);
			return (value);
		}
		current = current->next;
	}
	return (NULL);
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
