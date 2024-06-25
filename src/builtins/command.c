/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:49:40 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/25 10:30:23 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"




int command_exit(int c)
{
    exit((unsigned char)c);
}

int command_pwd(t_data *data, int fd)
{
	(void)data;
	char *pos;
	long size;

	size = 20;
	while (1)
	{
		pos = malloc((size_t)size * sizeof(char *));
		if (!pos)
			return (perror("malloc() error"), -1);
		if (getcwd(pos, (size_t)size) != NULL)
		{
			ft_putstr_fd(pos, fd);
			ft_putchar_fd('\n', fd);
			free(pos);
			break;
		}
		else
		{
			free(pos);
			size += size;
		}
    }
    return (0);
}

int	command_cd(t_data *data)
{
	// ici changer car ca doit etre le num de la commande
	char		*old_pwd;
	char		*new_value;
	
	old_pwd = ft_strdup(value_pwd(data->env_node));
	if (data->cmd->content[1])
	{
		new_value = ft_strjoin("/", data->cmd->content[1]);
		new_value = ft_strjoin(old_pwd, new_value);
	}
	if (!old_pwd)
		return (printf("error oldpwd"), -1);
	if (ft_strncmp(data->cmd->content[0], "cd", ft_strlen(data->cmd->content[0])) == 0 && !data->cmd->content[1])
		cd_to_home(data);
	if (ft_strncmp(data->cmd->content[0], "cd", ft_strlen(data->cmd->content[0])) == 0 && ft_strncmp(data->cmd->content[1], "..", ft_strlen(data->cmd->content[1])) == 0  )
	{
		change_old_pwd(data);
	}
	if (chdir(new_value) == 0)
	{
		printf("rentre dans la modif\n");
		printf("%s\n", new_value);
		modifyValue(data->env_node, "OLDPWD", old_pwd);
		modifyValue(data->env_node, "PWD", new_value);
	}
	else
		printf("%s\n", strerror(errno));
	return (0);
}

void	change_old_pwd(t_data *data)
{
	char	*old_pwd;

	old_pwd = ft_strdup(value_old_pwd(data->env_node));
	modifyValue(data->env_node, "OLDPWD", value_pwd(data->env_node));
	modifyValue(data->env_node, "PWD", old_pwd);
}

void modifyValue(t_node_env *head, const char *name, const char *newValue)
{
	
    while (head != NULL)
	{
        if (strcmp(head->name, name) == 0)
		{
			
            free(head->value);
            head->value = strdup(newValue);
			printf("nouvelle valeur apres cd  : %s\n", head->value);
            return ;
        }
        head = head->next;
    }
}

char	*value_old_pwd(t_node_env *head)
{
	t_node_env *current;
	
	current = head;
	 while (current != NULL)
	{
        if (strcmp(current->name, "OLDPWD") == 0)
            return (current->value);
        current = current->next;
    }
	return (0);
}

char	*value_pwd(t_node_env *head)
{
	t_node_env *current;
	
	current = head;
	 while (current != NULL)
	{
        if (strcmp(current->name, "PWD") == 0)
            return (current->value);
        current = current->next;
    }
	return (NULL);
}

int cd_to_home(t_data *data)
{
	t_node_env *copy;
	char		*old_pwd;
	
	old_pwd = ft_strdup(value_pwd(data->env_node));
	if (!old_pwd)
		return (printf("error oldpwd"), -1);
	copy = data->env_node;
	while (copy != NULL)
	{
		if (ft_strncmp(copy->name, "HOME", ft_strlen(copy->name)) == 0)
			break ;
		copy = copy->next;
	}
	if (!copy->value)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(copy->value) == 0)
	{
		modifyValue(data->env_node, "OLDPWD", old_pwd);
		modifyValue(data->env_node, "PWD", copy->value);
	}
		
	return (0);
}
