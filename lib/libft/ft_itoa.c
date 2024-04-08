/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:30:31 by rtruvelo          #+#    #+#             */
/*   Updated: 2023/11/23 13:54:13 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_int_len(int number)
{
	size_t	y;

	y = 0;
	if (number != 0)
	{
		while (number > 0)
		{
			number = number / 10;
			y++;
		}
	}
	else if (number == 0)
		y++;
	return (y);
}

static char	*ft_add_pos_number(size_t len, int n, char *str)
{
	while (len)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		if (len == 0)
			return (str);
		len--;
	}
	return (str);
}

static char	*ft_add_nega_number(size_t len, int n, char *str)
{
	size_t	i;

	i = 0;
	while (len)
	{
		if (len == 0)
			return (str);
		str[len--] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	str[0] = '-';
	str[len + i + 1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		sign;

	sign = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		sign = 1;
		n *= -1;
	}
	len = ft_int_len(n);
	str = malloc((len + 1 + sign) * sizeof(char));
	if (!str)
		return (NULL);
	str[len + sign] = '\0';
	if (sign == 1)
		return (ft_add_nega_number(len, n, str));
	else
		return (ft_add_pos_number(len, n, str));
}
// int main(void)
// {
//     // printf("%d\n", ft_int_len(11111));
//     printf("%s\n", ft_itoa(-13411));
//     //  printf("%d\n", ft_strlen(ft_itoa((-13411))));
//     printf("\n");
// }