/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:32 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/13 15:57:42 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */






#include "../mini/mini.h"


int	command_echo(t_data *data, char *value, int fd)
{
	ft_putstr_fd(value, fd);
	if (!data->arg)
		write(1, "/n", fd);
	return (0);
}

