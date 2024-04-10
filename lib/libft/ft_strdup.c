/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:32:51 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/10 14:29:02 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	size_t	i;
	size_t	y;
	char	*pointer;

	y = 0;
	i = ft_strlen(source) + 1;
	pointer = malloc(i * sizeof(char));
	if (!pointer)
		return (NULL);
	while (y < i)
	{
		pointer[y] = source[y];
		y++;
	}
	pointer[ft_strlen(source)] = '\0'; // changement ici
	return (pointer);
}
