/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:58:01 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/26 10:07:55 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	free_exec_part(t_data *data)
{
	int	i;

	i = 0;
	if (!data->free_pid)
	{
		if (data->pip)
		{
			while (data->pip[i])
			{
				free(data->pip[i]);
				i++;
			}
			if (data->pip)
				free(data->pip);
		}
		free(data->tab_pid);
		data->free_pid = true;
	}
	return (0);
}

int	free_env(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->env)
	{
		while (data->env[i])
		{
			free(data->env[i]);
			i++;
		}
		free(data->env);
		data->env = NULL;
	}
	return (0);
}

void	ft_lstclear(t_node_env **lst, void (*del)(void *))
{
	t_node_env	*current;
	t_node_env	*next;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

int	ft_lstclear_data(t_data *data)
{
	t_data	*ptr;
	int		last_pid;

	ptr = data;
	if (!ptr)
		return (0);
	last_pid = ptr->last_pid;
	if (ptr->cmd)
		ptr->cmd = ft_lstclear_cmd(ptr->cmd);
	if (ptr->env)
		free_env(ptr);
	if (ptr->env_node)
		ft_lstclear_env(ptr);
	if (ptr->path)
		free(ptr->path);
	if (ptr->str)
		free(ptr->str);
	if (!ptr->free_pid)
		ft_clear_exec(ptr);
	free(ptr);
	data = NULL;
	return (last_pid);
}

void	ft_clear_exec(t_data *ptr)
{
	int	i;

	i = 0;
	free(ptr->tab_pid);
	if (ptr->pip)
	{
		i = 0;
		while (ptr->pip[i])
		{
			free(ptr->pip[i]);
			i++;
		}
		free(ptr->pip);
	}
}
