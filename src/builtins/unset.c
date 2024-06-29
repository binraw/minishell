/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:45:17 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/29 12:57:39 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"
#include <stdio.h>

int	unset_command(t_data *data, char *value) 
{
	t_node_env	*ptr;
	t_node_env	*next;
	t_node_env	*prev;

	ptr = data->env_node;
	prev = NULL;
	while (ptr)
	{
		next = ptr->next;
		if (ft_strncmp(ptr->name, value, ft_strlen(value)) == 0)
			remove_env_node(ptr, prev);
		else
			prev = ptr;
		ptr = next;
	}
	return (0);
}

int remove_env_node(t_node_env *ptr, t_node_env *prev)
{
	if (!ptr)
		return (-1);
	if (prev)
		prev->next = ptr->next;
	if (ptr->content)
		free(ptr->content);
	if (ptr->name)
		free(ptr->name);
	if (ptr->value)
		free(ptr->value);
	free(ptr);
	return (0);
}
