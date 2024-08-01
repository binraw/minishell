/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:10:07 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/07/30 11:57:13 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

bool	parsing_error(char	*str)
{
	size_t	i;
	bool	error;
	int		quote;

	i = 0;
	error = false;
	quote = 0;
	if (!str)
		return (true);
	while (str[i] && !error)
	{
		quote = manage_quotes(str[i], quote);
		if (quote == 0 && str[i] == '>')
		{
			if (str[i + 1] == '>')
				i++;
			error = check_parsing_error(str, str[i], &i);
		}
		else if (quote == 0 && str[i] == '<')
		{
			if (str[i + 1] == '<')
				i++;
			error = check_parsing_error(str, str[i], &i);
		}
		else if (quote == 0 && str[i] == '|')
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
	while (ft_is_whitespace(str[*i]))
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
	write(2, "bash: syntax error near unexpected token `", 42);
	if (c == '\0' || c == '\n')
		write(2, "newline", 7);
	else
		write(2, &c, 1);
	write(2, "\'\n", 2);
	return (true);
}

bool	is_line_empty(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (!str[i])
		return (true);
	return (false);
}
