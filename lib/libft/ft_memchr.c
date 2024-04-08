/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:53:29 by rtruvelo          #+#    #+#             */
/*   Updated: 2023/11/20 12:52:50 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int ch, size_t count)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)ptr;
	while (i < count)
	{
		if (p[i] == (char)ch)
		{
			return (&p[i]);
		}
		i++;
	}
	return (NULL);
}
