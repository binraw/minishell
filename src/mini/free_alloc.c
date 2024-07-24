/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:58:01 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/24 12:21:16 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int	free_exec_part(t_data *data, int **pip, pid_t *tab_pid)
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
	if (tab_pid)
		free(tab_pid);
	return (0);
}
