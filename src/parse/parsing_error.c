/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:10:07 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/06/28 13:12:58 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

bool	parsing_error(char	*str)
{
	size_t	i;
	bool	error;

	i = 0;
	error = false;
	if (!str)
		return (true);
	while (str[i] && !error)
	{
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				i++;
			error = check_parsing_error(str, str[i], &i);
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				i++;
			error = check_parsing_error(str, str[i], &i);
		}
		else if (str[i] == '|')
			error = check_parsing_error(str, str[i], &i);
		else
			i++;
	}
	return (error);
}

bool	check_parsing_error(char *str, char c, size_t *i)
{
	*i = *i + 1;
	if (str[*i] == c)
		return (print_parsing_error(str[*i]));
	while (str[*i] == ' ' || str[*i] == '\t')
		*i = *i + 1;
	if (c == '|')
	{
		if (!str[*i] || str[*i] == '|')
			return (print_parsing_error(str[*i]));
	}
	else if (!str[*i] || str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
		return (print_parsing_error(str[*i]));
	return (false);
}

bool	print_parsing_error(char c)
{
	write(1, "minishell: syntax error near unexpected token `", 47);
	if (c == '\0' || c == '\n')
		write(1, "newline", 7);
	else
		write(1, &c, 1);
	write(1, "\'\n", 2);
	return (true);
}
