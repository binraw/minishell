/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:50:16 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/04 13:25:26 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"



int command_env(t_data *data, int fd)
{
 	t_node_env  *dup;

	dup = data->env_node;
	if (dup == NULL)
		ft_putstr_fd("NULL\n", fd);	
    while (dup)
    {
		ft_putstr_fd(dup->content, fd);
		ft_putstr_fd("\n", fd);
        dup = dup->next;
    }
    return (0);
}
