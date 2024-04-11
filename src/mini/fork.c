/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:57:06 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/11 13:57:50 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	create_fork(int i)
{
	pid_t	tab_fork;
	int	y;

	y = 0;
	tab_fork = malloc(i * sizeof(pid_t));	
	while (i > 0)
	{
		tab_fork[y] = fork();
		i--;			
	}
}