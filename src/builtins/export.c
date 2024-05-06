/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:15:19 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/06 15:52:10 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../mini/mini.h"
#include <stdio.h>
#include <string.h>


// a voir mais c'est possible que export rentre dans cette fonction
int	add_env_value(t_data *data, char *value_content)
{
	t_node_env *new_node;
	size_t		i;

	new_node = NULL;
	i = 0;
	while(value_content[i] && value_content[i] != '=')
		i++;
	new_node->name = malloc(i * sizeof(char));
	if (!new_node)
		return (-1);
	new_node->value = malloc((ft_strlen(value_content) - i) * sizeof(char));
	if (!new_node->value)
		return (free(new_node->name), -1);
	ft_strlcpy(new_node->name, value_content, i);
	ft_strlcpy(new_node->value, value_content + i, ft_strlen(value_content) - i);
	new_node->content = ft_strdup(value_content);
	if (!new_node->content)
	{
		free(new_node->name);
		free(new_node->value);
		return (-1);
	}

	ft_lstadd_back(data->env_node, new_node); 
	return (0);
}


int		remove_env_value(t_data *data, char *name_value)
{
	t_node_env *current_node;
    t_node_env *previous_node;

	current_node = data->env_node;
	previous_node = NULL;
	while (current_node)
	{
		if (ft_strncmp(current_node->name, name_value, ft_strlen(current_node->name)) == 0)
		{
            if (previous_node != NULL) {
                previous_node->next = current_node->next;
            } else {
                data->env_node = current_node->next;
            }
            free(current_node);
            return 1;
        }
        previous_node = current_node;
        current_node = current_node->next;

	}
	return (0);
}


t_node_env	*screen_export(t_data *data, int fd)
{
	t_node_env *current_node;
	t_node_env *second_node;
	char *max_value;
	size_t i;

	current_node = ft_lstduplicate(data->env_node);
	second_node = current_node;
	max_value = ft_strdup(data->env_node->name); // je dois faire un pointeur sur le next du next
	i = 0;
		while (current_node)
		{
			i = ft_strlen(current_node->name);
			if (i > ft_strlen(max_value))
			{
				i = ft_strlen(max_value);
			}
			if (ft_strncmp(current_node->name, max_value, i) > 0)
			{
				free(max_value);
				max_value = ft_strdup(current_node->content);
			}
			current_node = current_node->next;
		}
		while (current_node)
		{
			i = ft_strlen(current_node->name);
			if (i > ft_strlen(max_value))
			{
				i = ft_strlen(max_value);
			}

			if (ft_strncmp(current_node->content, max_value, i) == 0)
			{
				
			//	remove_node(&second_node, current_node);
				break ;
			}
			current_node = current_node->next;
		}
	ft_putstr_fd(max_value, fd);
	return (current_node);
}


