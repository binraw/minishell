/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:58:01 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/01 11:04:14 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int	free_exec_part(t_data *data)
{
	int i;
	int y;

	i = 0;
	y = 0;
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
	if (!data->free_pid)
	{
		free(data->tab_pid);
		data->free_pid = true;
	}
	return (0);
}
