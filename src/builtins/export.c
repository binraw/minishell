/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:15:19 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/04 09:35:03 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../mini/mini.h"
#include <stdio.h>
#include <string.h>

//il faut gerer le cas ou plusieurs variable sont creer en une seule commande export
int	add_env_value(t_data *data, char *value_content)
{
	t_node_env *new_node;
	size_t		i;

	new_node = NULL;
	i = 0;

	if ((control_export_value(value_content) == -1))
		return (-1);
	if ((control_export_name(data, value_content) == 1))
		return (0);

	new_node = ft_lstnew(value_content);
	if (!new_node->content)
	{
		free(new_node->name);
		free(new_node->value);
		return (-1);
	}

	ft_lstadd_back(data->env_node, new_node); 
	return (0);
}

int		control_export_name(t_data *data, char *value_content)
{
	char	*new_name;
	char	*new_value;
	t_node_env *head;
	size_t	i;

	new_value = NULL;
	new_name = NULL;
	i = 0;
	head = data->env_node;
	while(value_content[i] && value_content[i] != '=')
		i++;
	new_name = malloc(i + 1 * sizeof(char));
	new_value = malloc(ft_strlen((value_content + i)) * sizeof(char));
	ft_strlcpy(new_name, value_content, i);
	ft_strlcpy(new_value, value_content + i, ft_strlen(value_content) - i);

	while (data->env_node)
	{
		if ((ft_strncmp(data->env_node->name, new_name, ft_strlen(new_name)) == 0))
		{
			free(data->env_node->value);
			data->env_node->value  = ft_strdup(new_value);
			return (1);
		}
		data->env_node = data->env_node->next;
	}
	data->env_node = head;
	return (0);
}	


int		control_export_value(char *value_content)
{
	int i;

	i = 0;
	while(value_content[i])
	{
		if (value_content[i] == '$')
		{
			ft_putstr_fd("bash: export: `", 1);
			ft_putstr_fd(value_content + i, 1);
			ft_putstr_fd("`: not a valid identifier\n", 1);
			return (-1);
		}
		
		else if (value_content[i] == '!')
		{
			ft_putstr_fd("bash: ", 1);
			ft_putstr_fd(value_content, 1);
			ft_putstr_fd(": event not found", 1);
			return (-1);
		}
		else if (value_content[i] == '~')
		{
			ft_putstr_fd("bash: export: `", 1);
			ft_putstr_fd(value_content, 1);
			ft_putstr_fd("`: not a valid identifier\n", 1);
			return (-1);

		}
		i++;
	}
	if ((value_content[0] >= '0' && value_content[0] <= '9') || value_content[0] == '~')
	{
		ft_putstr_fd("bash: export: `", 1);
		ft_putstr_fd(value_content, 1);
		ft_putstr_fd("`: not a valid identifier\n", 1);
		return (-1);
	}
	if (value_content[0] == '!')
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(value_content, 1);
		ft_putstr_fd(": event not found", 1);
		return (-1);
	}

	return (0);
}




void	screen_export(t_data *data, int fd)
{
	t_node_env *current_node;
	char *max_value;
	size_t i;

	i = 0;
	current_node = data->env_node;
	max_value = ft_strdup("~~~~");
	while (current_node)
	{
		i = ft_strlen(current_node->name);
		if (ft_strncmp(current_node->name, max_value, i + 1) < 0 && current_node->print == false)
		{
			free(max_value);
			max_value = ft_strdup(current_node->content);
		}
		current_node = current_node->next;
	}
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(max_value, fd);
	ft_putchar_fd('\n', fd);
	current_node = data->env_node;
	while (current_node)
	{
		i = ft_strlen(current_node->name);
		if (ft_strncmp(current_node->content, max_value, i + 1) == 0)
		{
			current_node->print = true;
			free(max_value);
			return ;
		}
		current_node = current_node->next;
	}
}
	

int	ft_lstsize(t_node_env *head)
{
	size_t	i;
	t_node_env	*tmp;

	tmp = head;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	reset_print_env(t_data *data)
{
	t_node_env *current_node;

	current_node = data->env_node;
	while (current_node)
	{
		current_node->print = false;
		current_node = current_node->next;
	}

}
