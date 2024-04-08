/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:15:21 by rtruvelo          #+#    #+#             */
/*   Updated: 2023/11/22 17:42:06 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, size_t i, size_t count, char c);
static size_t	ft_count_letters(size_t start, char const *s, char c);
static void		*ft_free_malloc(char **str, size_t index);

char	**ft_split(char const *s, char c)
{
	char			**str;
	size_t			i;
	size_t			count;
	size_t			start;

	if (s == NULL)
		return (NULL);
	start = 0;
	i = 0;
	count = ft_count_words(s, i, 0, c);
	str = ft_calloc((count + 1), sizeof(char *));
	if (!str)
		return (NULL);
	while (count > i)
	{
		while (s[start] && (s[start] == c))
			start++;
		str[i] = ft_substr(s, start, ((ft_count_letters(start, s, c)) - start));
		if (str[i] == NULL)
			return (ft_free_malloc(str, i));
		start = ft_count_letters(start, s, c);
		i++;
	}
	return (str);
}

static size_t	ft_count_words(char const *s, size_t i, size_t count, char c)
{
	size_t	y;

	y = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && (s[i] != c))
		{
			i++;
			y++;
		}
		if (y != 0)
			count++;
		while (s[i] != '\0' && (s[i] == c))
			i++;
	}
	return (count);
}

static size_t	ft_count_letters(size_t start, char const *s, char c)
{
	while (s[start] && (s[start] != c))
		start++;
	return (start);
}

static void	*ft_free_malloc(char **str, size_t index)
{
	size_t	i;

	i = 0;
	while (index > i)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

// int main()
// {
// 	char *str = malloc(2147483650);
// 	memset(str, 'A', 2147483650);
// 	str[2147483649] = '\0';
// 	ft_split(str, 'b');
// }
