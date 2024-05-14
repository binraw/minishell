/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:45:17 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/14 15:36:13 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"
#include <stdio.h>

int	unset_command(t_data *data, char *value) 
{
	t_node_env *second_node;
	t_node_env *third_node;
	t_node_env *head;
	char		**multi_name;
	size_t		i;

	second_node = data->env_node->next;
	third_node = second_node->next;
	multi_name = init_cmd(value); // quand il y a plusieurs values alors segfault a voir pourquoi ?
	head = data->env_node;
	i = 0;
	while (multi_name[i])
	{
		while (third_node)
		{

			if (ft_strncmp(second_node->name, multi_name[i], ft_strlen(multi_name[i])) == 0)
			{
				remove_node(data->env_node, second_node, third_node);
				break ;
			}
			data->env_node = data->env_node->next;
			second_node = second_node->next;
			third_node = third_node->next;
	}
		data->env_node = head;
		i++;
	}
	return (0);
}



int remove_node(t_node_env *current_node, t_node_env *second_node, t_node_env *third_node)
{
	if (current_node == NULL || second_node == NULL)
	{
		// Gérer les cas où les nœuds sont NULL
		return (-1);
	}
	free(second_node);
	current_node->next = third_node;
	return (0);
}
 
