/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:27:14 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/07/24 13:40:21 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

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
	size_t		i;
	t_node_cmd	*ptr;
	t_redir		*r_ptr;
	t_rdocs		*rd_ptr;

	ptr = cmd;
	rd_ptr = NULL;
	while (ptr)
	{
		i = 0;
		while (ptr->content[i])
		{
			ptr->content[i] = ft_trim_quote(ptr->content[i]);
			i++;
		}
		r_ptr = ptr->redir;
		double_loop_trim_cmd_quote(ptr, rd_ptr, r_ptr);
		ptr = ptr->next;
	}
}

void	double_loop_trim_cmd_quote(t_node_cmd *ptr,
								t_rdocs *rd_ptr, t_redir *r_ptr)
{
	while (r_ptr)
	{
		r_ptr->content = ft_trim_quote(r_ptr->content);
		r_ptr = r_ptr->next;
	}
	rd_ptr = ptr->rdocs;
	while (rd_ptr)
	{
		rd_ptr->limit = ft_trim_quote(rd_ptr->limit);
		rd_ptr = rd_ptr->next;
	}
}

char	*ft_trim_quote(char	*str)
{
	size_t	len;
	char	*trim;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = quote_len(str);
	if (len == ft_strlen(str))
		return (str);
	trim = malloc(sizeof(char) * (len + 1));
	return (loop_trim_quote(trim, str, i, j));
}

size_t	quote_len(char *str)
{
	int		quote;
	size_t	len;
	size_t	i;

	quote = 0;
	len = 0;
	i = 0;
	while (str[i])
	{
		if (quote != manage_quotes(str[i], quote))
		{
			quote = manage_quotes(str[i], quote);
			i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
