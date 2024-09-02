/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:45:46 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/26 10:35:43 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"
#include <stdio.h>
#include <string.h>

void	empty_new_value(t_data *data, char *new_name)
{
	free(new_name);
	ft_lstclear_data(data);
	exit(1);
}

void	empty_new_name(t_data *data)
{
	ft_lstclear_data(data);
	exit(1);
}

int	control_export_value(char *value_content)
{
	int	i;

	i = 0;
	while (value_content[i])
	{
		if (write_error_export(value_content[i]) == -1)
			return (-1);
		i++;
	}
	if ((value_content[0] >= '0' && value_content[0] <= '9')
		|| value_content[0] == '~')
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(value_content, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		return (-1);
	}
	if (value_content[0] == '!')
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(value_content, 2);
		ft_putstr_fd(": event not found", 2);
		return (-1);
	}
	return (0);
}

int	write_error_export(char value)
{
	if (value == '$')
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd("$", 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		return (-1);
	}
	else if (value == '!')
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd("!", 2);
		ft_putstr_fd(": event not found", 2);
		return (-1);
	}
	else if (value == '~')
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd("~", 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		return (-1);
	}
	return (0);
}

void	fail_dup_export(t_data *data, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd("NULL", fd);
	ft_putstr_fd("\n", fd);
	ft_lstclear_data(data);
	exit(1);
}
