/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:27:14 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/06/26 11:26:31 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

// fonction pour gerer les quotes
int	manage_quotes(char c, int quote)
{
	if (c == '\"')
	{
		if (quote == 0)
			return (2);
		if (quote == 2)
			return (0);
	}
	else if (c == '\'')
	{
		if (quote == 0)
			return (1);
		if (quote == 1)
			return (0);
	}
	return (quote);
}

void	ft_trim_cmd_quote(t_node_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd)
	{
		while (cmd->content[i])
		{
			cmd->content[i] = ft_trim_quote(cmd->content[i]);
			i++;
		}
		while (cmd->redir)
		{
			cmd->redir->content = ft_trim_quote(cmd->redir->content);
			cmd->redir = cmd->redir->next;
		}
		while (cmd->rdocs)
		{
			cmd->rdocs->limit = ft_trim_quote(cmd->rdocs->limit);
			cmd->rdocs = cmd->rdocs->next;
		}
		cmd = cmd->next;
	}
}

char	*ft_trim_quote(char	*str)
{
	size_t	len;
	char	*trim;
	int		quote;
	size_t	i;
	size_t	j;

	quote = 0;
	i = 0;
	j = 0;
	len = quote_len(str);
	if (len == ft_strlen(str))
		return (str);
	trim = malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		if (quote != manage_quotes(str[i], quote))
		{
			quote = manage_quotes(str[i], quote);
			i++;
		}
		else
		{
			trim[j] = str[i];
			i++;
			j++;
		}
	}
	trim[j] = 0;
	free(str);
	return (trim);
}

size_t	quote_len(char *str)
{
	int		quote;
	size_t	len;

	quote = 0;
	len = 0;
	while (*str)
	{
		if (quote != manage_quotes(*str, quote))
		{
			quote = manage_quotes(*str, quote);
			str++;
		}
		else
		{
			str++;
			len++;
		}
	}
	return (len);
}
