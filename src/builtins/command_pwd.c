// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   command_pwd.c                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/21 16:34:47 by rtruvelo          #+#    #+#             //
//   Updated: 2024/08/31 10:57:15 by rtruvelo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../mini/mini.h"

int	command_pwd(t_data *data, int fd)
{
	char	*pos;
	long	size;

	size = 20;
	while (1)
	{
		pos = malloc((size_t)size * sizeof(char *));
		if (!pos)
			empty_pos(data);
		if (getcwd(pos, (size_t)size) != NULL)
		{
			ft_putstr_fd(pos, fd);
			ft_putchar_fd('\n', fd);
			free(pos);
			break ;
		}
		else
		{	
			free(pos);
			size += size;
			if (size > 100)
				return (1);
		}
	}
	return (1);
}

char	*value_pwd(t_node_env *head)
{
	t_node_env	*current;
	size_t		i;
	char		*value;

	i = 0;
	current = head;
	while (current != NULL)
	{
		if (strcmp(current->name, "PWD") == 0)
		{
			while (current->content[i] != '=' && current->content[i])
				i++;
			i++;
			value = ft_strdup((current->content + i));
			if (!value)
				return (NULL);
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}
