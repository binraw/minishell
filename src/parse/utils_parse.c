/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:30:43 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/26 11:42:17 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

t_node_cmd	*loop_cmd_get_content(t_node_cmd *cmd, char *str)
{
	size_t	i;
	char	*tok;

	i = 0;
	if (is_line_empty(str))
	{
		free(str);
		cmd->content[0] = NULL;
		return (cmd);
	}
	tok = ft_strtok(str, " \t\n\v\f\r", true);
	while (tok)
	{
		cmd->content[i] = tok;
		i++;
		tok = ft_strtok(NULL, " \t\n\v\f\r", true);
	}
	cmd->content[i] = NULL;
	free(str);
	return (cmd);
}

void	redir_manage_env(t_data *data, t_redir *redir)
{
	t_redir		*r_ptr;

	r_ptr = redir;
	while (r_ptr)
	{
		r_ptr->content = trim_env(data, r_ptr->content);
		r_ptr = r_ptr->next;
	}
}

char	*loop_trim_quote(char *trim, char *str, size_t i, size_t j)
{
	int	quote;

	quote = 0;
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

int	free_data_pips(t_data *data, char **pips, size_t size)
{
	size_t	i;

	i = 0;
	if (pips)
	{
		while (i < size)
		{
			free(pips[i]);
			i++;
		}
		free(pips);
	}
	ft_lstclear_data(data);
	return (EXIT_FAILURE);
}

size_t	loop_tok_pips(char *argv, char **pips)
{
	char		*tok;
	size_t		i;

	i = 0;
	tok = ft_strtok(argv, "|", false);
	while (tok)
	{
		pips[i] = tok;
		tok = ft_strtok(NULL, "|", false);
		i++;
	}
	return (i);
}
