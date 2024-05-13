/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:49:40 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/13 11:40:00 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int command_env(t_data *data)
{
    size_t i;

    i = 0;
    while (data->env[i])
    {
        printf("%s\n", data->env[i]);
        i++;
    }
    return (0);
}


int command_exit(int c)
{
    exit((unsigned char)c);
}

int command_pwd(t_data *data)
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
		printf("%s\n", pos);
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
	int i; // ici changer car ca doit etre le num de la commande
	char		*old_pwd;
	
	i = 0;
	old_pwd = ft_strdup(value_pwd(data->env_node));
	if (!old_pwd)
		return (printf("error oldpwd"), -1);
	if (ft_strncmp(data->cmd[i], "cd", ft_strlen(data->cmd[i])) == 0)
		cd_to_home(data);
	if (ft_strncmp(data->cmd[i], "cd ..", ft_strlen(data->cmd[i])) == 0)
	{
		change_old_pwd(data);
	}
	if (chdir(data->path) == 0)
	{
		modifyValue(data->env_node, "OLDPWD", old_pwd);
		modifyValue(data->env_node, "PWD", data->path);
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
    t_node_env *current;
	
	current = head;
    while (current != NULL)
	{
        if (strcmp(current->name, name) == 0)
		{
            free(current->value);
            current->value = strdup(newValue);
            return ;
        }
        current = current->next;
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
