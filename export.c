/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:15:19 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/03 16:11:40 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "lib/libft/libft.h"
#include "src/mini/mini.h"
#include <cstdio>


int	add_env_value(char *value_content)
{
	t_node_env *new_node;
	char		*str_value;
	size_t		i;

	i = 0;
	while(value_content[i] && value_content != '=')
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

	ft_lstadd_back(data->t_node_env, new_node); 
}


