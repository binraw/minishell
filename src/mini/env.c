/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:24:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/02 12:40:42 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_env(t_data *data)
{
	size_t	i;
	size_t	y;
	t_node_env	*copy;

	i = 0;
	y = 0;
	copy = data->env_node;
	while (copy->next != NULL)
	{
		copy = copy->next;
		y++;
	}
	data->env = malloc(sizeof(char*) * (y + 1));
	copy = data->env_node;
	if (!data->env)
		return (-1);
	while (i < y )
	{
		data->env[i] = ft_strdup(copy->content);
		if (!data->env[i])
			return (-1);
		copy = copy->next;
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

// int init_node_env(t_data *data)
// {
//     int i;
//     t_node_env *new_node;

//     i = 0;
//     data->env_node = ft_lstnew(data, data->env[i]);
//     while (data->env[++i])
//     {
//         new_node = ft_lstnew(data, data->env[i]);
//         if (!new_node)
//             return (-1);
//         ft_lstadd_back(&(data->env_node), new_node);
//     }
//     return (0);
// }

// int	maj_env(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->env_node[i] =
// }

int init_node_env(t_data *data, char **envp)
{
    int i;
    t_node_env *new_node;

    i = 0;
    data->env_node = ft_lstnew(data, envp[i]);
    while (envp[++i])
    {
        new_node = ft_lstnew(data, envp[i]);
        if (!new_node)
            return (-1);
        ft_lstadd_back(&(data->env_node), new_node);
    }
    return (0);
}