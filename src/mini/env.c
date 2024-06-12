/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:51:18 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/06 15:51:23 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_env(t_data *data)
{
	size_t	y;
	t_node_env	*copy;

	y = 0;
	copy = data->env_node;
	while (copy != NULL)
	{
		copy = copy->next;
		y++;
	}
	data->env = malloc(sizeof(char*) * (y + 1));
	if (!data->env)
		return (-1);
	copy_env_tab(data, y);
	return (0);
}


int copy_env_tab(t_data *data, size_t y)
{
	size_t	i;
	t_node_env	*dup;

	i = 0;
	dup = data->env_node;
	while (i < y)
	{
		data->env[i] = ft_strdup(dup->content);
		if (!data->env[i])
			return (-1);
		dup = dup->next;
		i++;
	}
	data->env[i] = NULL;
	return (0);
}





int free_env(t_data *data)
{
	size_t i;

	i = 0;
	if (data->env)
	{
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	// free(data->env);
	data->env = NULL;
	}
	return (0);
}


int init_node_env(t_data *data, char **envp)
{
    int i;
    t_node_env *new_node;

    i = 0;
    data->env_node = ft_lstnew(envp[i]);
    while (envp[++i])
    {
        new_node = ft_lstnew(envp[i]);
        if (!new_node)
            return (-1);
        ft_lstadd_back(data->env_node, new_node);
    }
    return (0);
}
