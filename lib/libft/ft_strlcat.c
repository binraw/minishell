/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:37:04 by rtruvelo          #+#    #+#             */
/*   Updated: 2023/11/16 14:02:13 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	y;
	size_t	len;

	i = ft_strlen(dest);
	y = 0;
	len = i;
	if (size <= ft_strlen(dest))
		return (size + ft_strlen(src));
	while (src[y] != '\0' && i < (size - 1))
	{
		dest[i] = src[y];
		i++;
		y++;
	}
	dest[i] = '\0';
	return (len + ft_strlen(src));
}
