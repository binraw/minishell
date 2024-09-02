/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:37:33 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/26 10:39:39 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"
#include <stdio.h>
#include <string.h>

char	*asign_max_export(t_node_env *current_node,
							char *max_value, char **value)
{
	size_t	i;

	while (current_node)
	{
		i = ft_strlen(current_node->name);
		if (ft_strncmp(current_node->name,
				max_value, i + 1) < 0
			&& current_node->print == false)
		{
			free(max_value);
			free(value);
			max_value = ft_strdup(current_node->content);
		}
		current_node = current_node->next;
	}
	return (max_value);
}

void	print_export(char **value, int fd)
{
	size_t	y;

	y = 0;
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(value[0], fd);
	ft_putstr_fd("=\"", fd);
	while (value[++y])
	{
		if (y > 1)
			ft_putstr_fd("=", fd);
		ft_putstr_fd(value[y], fd);
	}
	ft_putstr_fd("\"", fd);
	ft_putchar_fd('\n', fd);
}

void	asign_print(t_node_env *current_node, char *max_value, char **value)
{
	size_t	i;
	size_t	y;

	while (current_node)
	{
		i = ft_strlen(current_node->name);
		if (ft_strncmp(current_node->content, max_value, i + 1) == 0)
		{
			current_node->print = true;
			free(max_value);
			y = 0;
			while (value[y])
			{
				free(value[y]);
				y++;
			}
			free(value);
			return ;
		}
		current_node = current_node->next;
	}
}

int	ft_lstsize(t_node_env *head)
{
	size_t		i;
	t_node_env	*tmp;

	tmp = head;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	reset_print_env(t_data *data)
{
	t_node_env	*current_node;

	current_node = data->env_node;
	while (current_node)
	{
		current_node->print = false;
		current_node = current_node->next;
	}
}
