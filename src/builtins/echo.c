/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:32 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/15 14:01:39 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */






#include "../mini/mini.h"


int	command_echo(t_data *data, char *value)
{
	size_t i;
	bool arg;

	i = 0;
	arg = false;
	if (value[0] == '-')
		i++;
	while (value[i] == 'n')
		i++;
	if (i > 1)
		arg = true;
	ft_putstr_fd(value, STDOUT_FILENO);
	if (arg == false)
		ft_putstr_fd("/n", STDOUT_FILENO);
	return (0);
}

