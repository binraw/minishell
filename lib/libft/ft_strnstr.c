/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:55:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/03/20 11:01:38 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;
	size_t	y;

	str1 = (char *) s1;
	str2 = (char *) s2;
	i = 0;
	y = 0;
	if (s2[i] == '\0')
		return (str1);
	while (str1[i] != '\0' && i < n)
	{
		while ((str1[i + y] == str2[y]) && str1[i + y] != '\0' && i + y < n)
			y++;
		if (str2[y] == '\0')
		{
			return (str1 + i);
		}
		i++;
		y = 0;
	}
	return (NULL);
}
