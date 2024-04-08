/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:37:34 by rtruvelo          #+#    #+#             */
/*   Updated: 2023/11/23 12:56:40 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	size_t	x;
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = ft_strlen(s1) + ft_strlen(s2)+ 1;
	x = 0;
	y = 0;
	dest = malloc(sizeof(char) * i);
	if (!dest)
		return (NULL);
	while (s1[y] != '\0')
		dest[x++] = s1[y++];
	y = 0;
	while (s2[y] != '\0')
		dest[x++] = s2[y++];
	dest[x] = '\0';
	return (dest);
}
