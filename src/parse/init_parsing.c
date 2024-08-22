/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:24:07 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/01 10:59:48 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int	init_cmd(t_data *data, char *argv)
{
	char		**pips;
	size_t		i;
	char		*tok;

	i = 0;
	if (is_line_empty(argv))
	{
		data->cmd = NULL;
		return (0);
	}
	if (parsing_error(argv))
	{
		data->last_pid = 2;
		data->cmd = NULL;
		return (0);
	}
	data->number_of_pip = ft_count_str(argv, '|') - 1;
	data->number_of_cmd = data->number_of_pip + 1;
	pips = malloc(sizeof(char *) * (data->number_of_cmd + 1));
	tok = ft_strtok(argv, "|", false);
	while (tok)
	{
		pips[i] = tok;
		tok = ft_strtok(NULL, "|", false);
		i++;
	}
	pips[i] = NULL;
	fill_cmd_content(data, pips);
	ft_trim_cmd_quote(data->cmd);
	return (1);
}

void	fill_cmd_content(t_data *data, char **pips)
{
	size_t		i;
	t_node_cmd	*ptr;

	i = 1;
	data->cmd = cmd_get_content(pips[0], 0, data);
	ptr = data->cmd;
	while (pips[i])
	{
		ptr->next = cmd_get_content(pips[i], i, data);
		ptr = ptr->next;
		i++;
	}
	free(pips);
}

t_node_cmd	*cmd_get_content(char *str, size_t index, t_data *data)
{
	size_t		i;
	char		*tok;
	t_node_cmd	*cmd;

	i = 0;
	cmd = ft_lstnew_cmd(index);
	cmd = cmd_get_redir(ft_strdup(str), cmd);
	str = clean_redir(str);
	str = trim_env(data, str);
	redir_manage_env(data, cmd->redir);
	cmd->content = malloc(sizeof(char *) * (ft_count_cmd(str) + 1));
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

t_node_cmd	*cmd_get_redir(char *str, t_node_cmd *cmd)
{
	char		*tok;

	cmd->redir = NULL;
	cmd->rdocs = NULL;
	tok = ft_strtok(str, " \t\n\v\f\r", true);
	while (tok)
	{
		if (*tok == '>' || *tok == '<')
			fill_redirs(tok, &cmd->redir, &cmd->rdocs);
		else
			free(tok);
		tok = ft_strtok(NULL, " \t\n\v\f\r", true);
	}
	free(str);
	return (cmd);
}

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
			while (str[i] == '>' || str[i] == '<')
				i++;
			while (ft_is_whitespace(str[i]))
				i++;
			while (str[i])
			{
				quote = manage_quotes(str[i], quote);
				if (quote == 0 && ft_is_whitespace(str[i]))
					break ;
				i++;
			}
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
	size_t	j;
	char	*clean;
	int		quote;

	i = 0;
	j = 0;
	quote = 0;
	if (!str)
		return (NULL);
	clean = malloc(sizeof(char) * (clean_redir_len(str) + 1));
	while (str[i])
	{
		if (quote == 0 && (str[i] == '<' || str[i] == '>'))
		{
			while (str[i] == '>' || str[i] == '<')
				i++;
			while (ft_is_whitespace(str[i]))
				i++;
			while (str[i])
			{
				quote = manage_quotes(str[i], quote);
				if (quote == 0 && ft_is_whitespace(str[i]))
					break ;
				i++;
			}
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

size_t	ft_count_cmd(char *str)
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
		{
			if (quote == 0 && (i == 0 || ft_is_whitespace(str[i - 1])))
				count++;
			quote = manage_quotes(str[i], quote);
			i++;
		}
		else if (quote == 0 && !ft_is_whitespace(str[i]) && (i == 0 || ft_is_whitespace(str[i - 1])))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}
