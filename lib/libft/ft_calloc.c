/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:53:37 by rtruvelo          #+#    #+#             */
/*   Updated: 2023/11/22 17:46:18 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*pointer;
	size_t	i;

	i = 0;
	if (!num || !size)
		return (malloc(0));
	if (SIZE_MAX / num < size)
		return (NULL);
	pointer = malloc(num * size);
	if (!pointer)
		return (NULL);
	while (i < (num * size))
	{
		pointer[i] = 0;
		i++;
	}
	return (pointer);
}
