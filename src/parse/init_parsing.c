/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:24:07 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/26 10:06:37 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int	init_cmd(t_data *data, char *argv)
{
	char		**pips;
	size_t		i;

	if (is_line_empty(argv))
		return (process_line_empty(data));
	if (parsing_error(argv))
		return (process_parsing_error(data));
	data->number_of_pip = ft_count_str(argv, '|') - 1;
	data->number_of_cmd = data->number_of_pip + 1;
	pips = malloc(sizeof(char *) * (data->number_of_cmd + 1));
	if (!pips)
		exit(free_data_pips(data, NULL, 0));
	i = loop_tok_pips(argv, pips);
	if (i < (size_t)(data->number_of_cmd))
		exit(free_data_pips(data, pips, i));
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
	if (!data->cmd)
		exit(free_data_pips(data, pips, data->number_of_cmd));
	ptr = data->cmd;
	while (pips[i])
	{
		ptr->next = cmd_get_content(pips[i], i, data);
		if (!ptr->next)
			exit(free_data_pips(data, &pips[i], data->number_of_cmd - i));
		ptr = ptr->next;
		i++;
	}
	free(pips);
}

t_node_cmd	*cmd_get_content(char *str, size_t index, t_data *data)
{
	t_node_cmd	*cmd;

	cmd = ft_lstnew_cmd(index);
	if (!cmd)
		return (NULL);
	cmd = cmd_get_redir(ft_strdup(str), cmd);
	str = clean_redir(str);
	if (!str)
		return (ft_lstclear_cmd(cmd), NULL);
	str = trim_env(data, str);
	if (!str)
		return (ft_lstclear_cmd(cmd), NULL);
	redir_manage_env(data, cmd->redir);
	cmd->content = malloc(sizeof(char *) * (ft_count_cmd(str) + 1));
	if (!cmd->content)
		return (ft_lstclear_cmd(cmd), NULL);
	return (loop_cmd_get_content(cmd, str));
}

t_node_cmd	*cmd_get_redir(char *str, t_node_cmd *cmd)
{
	char		*tok;

	cmd->redir = NULL;
	cmd->rdocs = NULL;
	if (!str)
		return (cmd);
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

size_t	ft_count_cmd(char *str)
{
	size_t		count;
	int			quote;

	count = 0;
	quote = 0;
	if (!str)
		return (0);
	return (loop_count_cmd(str, count, quote));
}
