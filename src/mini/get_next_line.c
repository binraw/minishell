/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:59:11 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/01/26 14:52:52 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t		cut_lign(char *str);
char		*finaly_str(char *buffer, size_t len);
void		*ft_memmove2(void *dest, void *src, size_t n);
char		*create_str(char *buffer, int fd);

char	*get_next_line(int fd)
{
	char			*finaly;
	char			*str;
	static char		buffer[BUFFER_SIZE + 1] = "\0";
	size_t			len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		len = 0;
		while (buffer[len] != '\0')
			buffer[len++] = '\0';
		return (NULL);
	}
	str = create_str(buffer, fd);
	if (!str)
		return (NULL);
	len = 0;
	len = cut_lign(str);
	finaly = finaly_str(str, len);
	if (ft_strlen2(str) != len)
		ft_memmove2(buffer, str + len + 1, ft_strlen2(str) - cut_lign(str));
	else
		buffer[0] = '\0';
	free(str);
	return (finaly);
}

char	*create_str(char *buffer, int fd)
{
	char		*str;
	ssize_t		re;

	re = 1;
	str = ft_strdup2(buffer);
	if (!str)
		return (NULL);
	while (re > 0 && (!ft_strchr2(str, '\n')))
	{
		re = read(fd, buffer, BUFFER_SIZE);
		if (re != 0)
			buffer[re] = '\0';
		if (re == 0 && buffer[0] == '\0')
		{
			free(str);
			return (NULL);
		}
		if (re != 0)
			str = ft_strjoin2(str, buffer);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*finaly_str(char *buffer, size_t len)
{
	char	*finaly;
	size_t	i;

	i = 0;
	finaly = malloc((len + 2) * sizeof(char));
	if (!finaly)
		return (NULL);
	if (len + 1 > 0)
	{
		while (buffer[i] != '\0' && i < (len))
		{
			finaly[i] = buffer[i];
			i++;
		}
		finaly[i] = 0;
	}
	if (ft_strlen2(buffer) > len)
		finaly[len] = '\n';
	finaly[len + 1] = '\0';
	return (finaly);
}

void	*ft_memmove2(void *dest, void *src, size_t n)
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

size_t	cut_lign(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}
// int main(void)
// {
//
// 	int fd;
// 	int i;
//
// 	i = 0;
//
// 	fd = open("bible.txt", O_RDONLY);
//
// 	while (i < 100)
// 	{
// 		get_next_line(fd);
// 		i++;
// 	}
// }
