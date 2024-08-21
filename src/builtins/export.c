/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:15:19 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/31 11:36:57 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"
#include <stdio.h>
#include <string.h>

int	add_env_value(t_data *data, char *value_content)
{
	t_node_env	*new_node;

	new_node = NULL;
	if ((control_export_value(value_content) == -1))
		return (-1);
	if ((control_export_name(data, value_content) == 1))
		return (0);
	new_node = ft_lstnew(ft_strdup(value_content));
	if (!new_node->content)
	{
		free(new_node->name);
		free(new_node->value);
		return (-1);
	}
	ft_lstadd_back(data->env_node, new_node);
	return (0);
}

int	control_export_name(t_data *data, char *value_content)
{
	char		*new_name;
	char		*new_value;
	size_t		i;

	new_value = NULL;
	new_name = NULL;
	i = 0;
	while (value_content[i] && value_content[i] != '=')
		i++;
	new_name = malloc(i + 1 * sizeof(char));
	if (!new_name)
		empty_new_name(data);
	new_value = malloc(ft_strlen((value_content + i)) * sizeof(char));
	if (!new_value)
		empty_new_value(data, new_name);
	ft_strlcpy(new_name, value_content, i + 1);
	ft_strlcpy(new_value, value_content + i + 1, ft_strlen(value_content) - i);
	if (action_change_export(data, new_value, new_name, value_content) == 1)
		return (1);
	free(new_name);
	free(new_value);
	return (0);
}

int	action_change_export(t_data *data, char *new_value,
						char *new_name, char *value_content)
{
	t_node_env	*head;

	head = data->env_node;
	while (head)
	{
		if ((ft_strncmp(head->name, new_name, ft_strlen(new_name) + 1) == 0))
		{
			change_value_export(data, head, new_name, new_value);
			head->content = ft_strdup(value_content);
			if (!head->content)
			{
				free(new_name);
				free(new_value);
				free(head->value);
				ft_lstclear_data(data);
				exit(1);
			}
			free(new_name);
			free(new_value);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

// void	empty_new_value(t_data *data, char *new_name)
// {
// 	free(new_name);
// 	ft_lstclear_data(data);
// 	exit(1);
// }
//
// void	empty_new_name(t_data *data)
// {
// 	ft_lstclear_data(data);
// 	exit(1);
// }

int	change_value_export(t_data *data, t_node_env *head,
						char *new_name, char *new_value)
{
	free(head->value);
	free(head->content);
	head->value = ft_strdup(new_value);
	if (!head->value)
	{
		free(new_name);
		free(new_value);
		ft_lstclear_data(data);
		exit(1);
	}
	return (1);
}

void	screen_export(t_data *data, int fd)
{
	t_node_env	*current_node;
	char		*max_value;
	char		**value;
	size_t		i;

	i = 0;
	current_node = data->env_node;
	max_value = ft_strdup("~~~~");
	if (!max_value)
		fail_dup_export(data, fd);
	value = NULL;
	max_value = asign_max_export(current_node, max_value, value);
	value = ft_split(max_value, '=');
	if (!value)
	{
		free(max_value);
		return ;
	}
	if (value[0][0] != '_')
		print_export(value, fd);
	current_node = data->env_node;
	asign_print(current_node, max_value, value);
}
