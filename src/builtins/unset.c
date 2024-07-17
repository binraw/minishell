/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:45:17 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/17 13:12:24 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"
#include <stdio.h>

int	unset_command(t_data *data, char **content) 
{
	t_node_env	*ptr;
	t_node_env	*next;
	t_node_env	*prev;
	size_t		i;

	i = 0;
	while (content[i])
	{
		ptr = data->env_node;
		prev = NULL;
		while (ptr)
		{
			next = ptr->next;
			if (ft_strncmp(ptr->name, content[i], ft_strlen(content[i])) == 0)
				remove_env_node(ptr, prev);
			else
				prev = ptr;
			ptr = next;
		}
		i++;
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
