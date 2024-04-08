/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:34:05 by rtruvelo          #+#    #+#             */
/*   Updated: 2023/11/15 21:27:30 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;

	if (dest == src || n == 0)
		return (dest);
	if (dest < src)
	{
		destination = (unsigned char *)dest;
		source = (unsigned char *)src;
		while (n--)
			*destination++ = *source++;
	}
	else
	{
		destination = (unsigned char *)dest + (n - 1);
		source = (unsigned char *)src + (n - 1);
		while (n--)
			*destination-- = *source--;
	}
	return (dest);
}
