/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:26:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/26 10:42:09 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int	process_line_empty(t_data *data)
{
	data->cmd = NULL;
	return (0);
}

int	process_parsing_error(t_data *data)
{
	data->last_pid = 2;
	data->cmd = NULL;
	return (0);
}

int	double_loop_clean_redir_len(char *str, size_t i)
{
	while (str[i] == '>' || str[i] == '<')
		i++;
	while (ft_is_whitespace(str[i]))
		i++;
	return (i);
}

int	loop_clean_redir_len(char *str, size_t i, int quote)
{
	while (str[i])
	{
		quote = manage_quotes(str[i], quote);
		if (quote == 0 && ft_is_whitespace(str[i]))
			break ;
		i++;
	}
	return (i);
}

size_t	loop_count_cmd(char *str, size_t count, int quote)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quote == 0 && (i == 0 || ft_is_whitespace(str[i - 1])))
				count++;
			quote = manage_quotes(str[i], quote);
			i++;
		}
		else if (quote == 0 && !ft_is_whitespace(str[i])
			&& (i == 0 || ft_is_whitespace(str[i - 1])))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}
