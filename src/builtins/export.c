/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:15:19 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/14 11:34:41 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../mini/mini.h"
#include <stdio.h>
#include <string.h>


// a voir mais c'est possible que export rentre dans cette fonction
int	add_env_value(t_data *data, char *value_content)
{
	t_node_env *new_node;
	size_t		i;

	new_node = NULL;
	i = 0;
	if ((control_export_value(value_content) == -1))
		return (-1);
	while(value_content[i] && value_content[i] != '=')
		i++;
	new_node->name = malloc(i * sizeof(char));
	if (!new_node)
		return (-1);
	new_node->value = malloc((ft_strlen(value_content) - i) * sizeof(char));
	if (!new_node->value)
		return (free(new_node->name), -1);
	ft_strlcpy(new_node->name, value_content, i); // rajoute une le fait que quand add un export qui existe deja change seulement son content
	ft_strlcpy(new_node->value, value_content + i, ft_strlen(value_content) - i);
	new_node->content = ft_strdup(value_content);
	if (!new_node->content)
	{
		free(new_node->name);
		free(new_node->value);
		return (-1);
	}

	ft_lstadd_back(data->env_node, new_node); 
	return (0);
}

int		control_export_value(char *value_content)
{
	if (value_content[0] == '$')
	{	
		ft_putstr_fd("bash: export: `", 1);
		ft_putstr_fd(value_content, 1);
		ft_putstr_fd("`: not a valid identifier\n", 1);
		return (-1);
	}
	if ((value_content[0] >= '0' && value_content[0] <= '9') || value_content[0] == '~')
	{
		ft_putstr_fd("bash: export: `", 1);
		ft_putstr_fd(value_content, 1);
		ft_putstr_fd("`: not a valid identifier\n", 1);
		return (-1);
	}
	if (value_content[0] == '!')
	{	
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(value_content, 1);
		ft_putstr_fd(": event not found", 1);
		return (-1);
	}

	return (0);
}


int	unset_command(t_data *data, char *value)
{
	t_node_env *second_node;
	t_node_env *third_node;

	second_node = data->env_node->next;
	third_node = second_node->next;

	while (third_node)
	{

		if (ft_strncmp(second_node->content, value, ft_strlen(value)) == 0)
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
	if (current_node == NULL || second_node == NULL || third_node == NULL)
	{
		// Gérer les cas où les nœuds sont NULL
		return (-1);
	}
	free(second_node);
	current_node->next = third_node;
	return (0);
}


void	screen_export(t_data *data, int fd)
{
	t_node_env *current_node;
	char *max_value;
	size_t i;

	i = 0;
	current_node = data->env_node;
	max_value = ft_strdup("~~~~"); // j'ai mis un A pour que tout passe avant mais si le Name est A jsais pas faut voir
	while (current_node)
	{
		i = ft_strlen(current_node->name);
		if (ft_strncmp(current_node->name, max_value, i + 1) < 0 && current_node->print == false)
		{
			free(max_value);
			max_value = ft_strdup(current_node->content);
		}
		current_node = current_node->next;
	}
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(max_value, fd);
	ft_putchar_fd('\n', fd);
	current_node = data->env_node;
	while (current_node)
	{
		i = ft_strlen(current_node->name);
		if (ft_strncmp(current_node->content, max_value, i + 1) == 0)
		{
			current_node->print = true;
			free(max_value);
			return ;
		}
		current_node = current_node->next;
	}
}
	

int	ft_lstsize(t_node_env *head)
{
	size_t	i;
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
