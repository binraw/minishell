/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:46:52 by rtruvelo          #+#    #+#             */
/*   Updated: 2023/12/13 17:13:56 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup2(char *source);
char	*ft_strjoin2(char	*s1, char	*s2);
size_t	ft_strlen2(char	*str);
char	*ft_concate_str(char	*s1, char	*s2, char *dest);

char	*ft_strchr2(char *string, int searchedChar)
{
	size_t	i;
	char	*p;
	char	search;

	i = 0;
	p = (char *)string;
	search = (char)searchedChar;
	while (p[i] != '\0')
	{
		if (p[i] == search)
		{
			return (&p[i]);
		}
		i++;
	}
	if (p[i] == search)
	{
		return (&p[i]);
	}
	if (search == '\0')
		return (NULL);
	return (0);
}

char	*ft_strjoin2(char	*s1, char	*s2)
{
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup2(s2));
	if (!s2)
		return (ft_strdup2(s1));
	dest = malloc(sizeof(char) * (ft_strlen2(s1) + ft_strlen2(s2) + 1));
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	return (ft_concate_str(s1, s2, dest));
}

char	*ft_concate_str(char	*s1, char	*s2, char *dest)
{
	size_t	y;
	size_t	x;

	x = 0;
	y = 0;
	while (s1[y] != '\0')
		dest[x++] = s1[y++];
	y = 0;
	while (s2[y] != '\0')
		dest[x++] = s2[y++];
	dest[x] = '\0';
	free(s1);
	return (dest);
}

char	*ft_strdup2(char	*source)
{
	size_t	i;
	size_t	y;
	char	*pointer;

	if (!source)
		return (NULL);
	y = 0;
	i = ft_strlen2(source);
	pointer = malloc((i + 1) * sizeof(char));
	if (!pointer)
		return (NULL);
	while (y < i)
	{
		pointer[y] = source[y];
		y++;
	}
	pointer[y] = '\0';
	return (pointer);
}

size_t	ft_strlen2(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
