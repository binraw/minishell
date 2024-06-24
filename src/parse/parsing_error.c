/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:54:17 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/06/18 14:26:33 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int	check_error_cmd(char *arg, char *tokens)
{
	size_t	i;
	char	c;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '>' || arg[i] == '<')
		{
			c = arg[i];
			if (!arg[i + 1])
				return (parsing_error_print("newline"));
			if (arg[i + 1] == c)
			{
				if (!arg[i + 2])
					return (parsing_error_print("newline"));
				if (ft_strchr(tokens ,arg[i + 2]))
				{
					c = arg[i + 2];
					return (parsing_error_print(&c));
				}
				i++;
			}
			else if (ft_strchr(tokens ,arg[i + 1]))
			{
				c = arg[i + 1];
				return (parsing_error_print(&c));
			}
			i++;
		}
		i++;
	}
	return (0);
}

int	parsing_error_print(char *str)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
	return (1);
}