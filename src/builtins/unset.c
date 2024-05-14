/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:45:17 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/14 14:48:56 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int	unset_command(t_data *data, char *value)
{
	t_node_env *second_node;
	t_node_env *third_node;

	second_node = data->env_node->next;
	third_node = second_node->next;

	while (third_node)
	{

		if (ft_strncmp(second_node->name, value, ft_strlen(value)) == 0)
		{
			remove_node(data->env_node, second_node, third_node);
			break ;
		}
		data->env_node = data->env_node->next;
		second_node = second_node->next;
		third_node = third_node->next;
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

