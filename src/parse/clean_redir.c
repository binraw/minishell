// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   clean_redir.c                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/24 13:28:30 by rtruvelo          #+#    #+#             //
//   Updated: 2024/08/24 13:43:33 by rtruvelo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../mini/mini.h"

size_t	clean_redir_len(char *str)
{
	size_t	i;
	size_t	len;
	int		quote;

	i = 0;
	len = 0;
	quote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (quote == 0 && (str[i] == '<' || str[i] == '>'))
		{
			i = double_loop_clean_redir_len(str, i);
			i = loop_clean_redir_len(str, i, quote);
		}
		else
		{
			quote = manage_quotes(str[i], quote);
			i++;
			len++;
		}
	}
	return (len);
}

char	*clean_redir(char *str)
{
	size_t	i;
	char	*clean;
	int		quote;

	i = 0;
	quote = 0;
	if (!str)
		return (NULL);
	clean = malloc(sizeof(char) * (clean_redir_len(str) + 1));
	return (create_clean(str, clean, quote, i));
}

char	*create_clean(char *str, char *clean, int quote, size_t i)
{
	size_t	j;

	j = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '<' || str[i] == '>'))
		{
			i = double_loop_clean_redir_len(str, i);
			i = loop_clean_redir_len(str, i, quote);
		}
		else
		{
			clean[j] = str[i];
			quote = manage_quotes(str[i], quote);
			i++;
			j++;
		}
	}
	clean[j] = '\0';
	free(str);
	return (clean);
}

size_t	ft_count_str(char *str, char sep)
{
	size_t		i;
	size_t		count;
	int			quote;

	i = 0;
	count = 0;
	quote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = manage_quotes(str[i], quote);
		if (i != 0 && str[i] == sep && str[i - 1] != sep && quote == 0)
			count++;
		i++;
	}
	if (i != 0 && str[i - 1] != sep)
		count++;
	return (count);
}

bool	ft_is_whitespace(char c)
{
	if (c == ' ')
		return (true);
	if (c >= 9 && c <= 13)
		return (true);
	return (false);
}
