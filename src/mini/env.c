/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:24:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/30 11:11:12 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_env(t_data *data, char **envp)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	while (envp[y])
		y++;
	data->env = malloc(sizeof(char**) * (y + 1) );
	if (!data->env)
		return (-1);
	while (i < y )
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			return (-1);
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
		free(data->env[i++]);
	}
	free(data->env);
	data->env = NULL;
	}
	return (0);
}

int init_node_env(t_data *data)
{
    int i;
    t_node_env *new_node;

    i = 0;
    data->env_node = ft_lstnew(data->env[i]);
    while (data->env[++i])
    {
        new_node = ft_lstnew(data->env[i]);
        if (!new_node)
            return (-1);
        ft_lstadd_back(&(data->env_node), new_node);
    }
    return (0);
}
