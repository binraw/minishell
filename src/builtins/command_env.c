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



int command_env(t_data *data)
{
 	t_node_env  *dup;

	dup = data->env_node;
	if (dup == NULL)
		printf("NULL\n");
    while (dup)
    {
        printf("%s\n", dup->content);
        dup = dup->next;
    }
    return (0);
}
