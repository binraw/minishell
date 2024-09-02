/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:40:22 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/09/02 10:43:57 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

void	ft_lstclear_content(t_node_cmd *current)
{
	size_t	i;

	i = 0;
	while (current->content[i])
	{
		free(current->content[i]);
		i++;
	}
	free(current->content[i]);
	free(current->content);
}
