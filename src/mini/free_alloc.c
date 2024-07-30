/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:58:01 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/30 11:10:15 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int	free_exec_part(t_data *data, int **pip)
{
	int i;
	int y;
	
	i = 0;
	y = 0;
	if (pip)
	{
		while (i < data->number_of_pip)
		{
			free(pip[i]);
			i++;
		}
		free(pip);
	}
	if (data->tab_pid)
	{
		free(data->tab_pid);
		data->tab_pid = NULL;
	}
	return (0);
}
