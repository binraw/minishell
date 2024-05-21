/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:24:07 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/21 11:16:26 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

/*char	**init_cmd(t_data *data ,char *argv)*/
/*{*/
/*	char **cmd;*/
/*	int		y;*/
/**/
/*	y = 0;*/
/*	if (argv[y] == '\0')*/
/*		return (NULL);*/
/*	while (argv[y] == ' ')*/
/*	{*/
/*		if (argv[y + 1] == '\0')*/
/*			return (NULL);*/
/*		y++;*/
/*	}*/
/*	cmd = ft_split(argv, '|');*/
/**/
/*	init_node_cmd(data, cmd);*/
/**/
/**/
/**/
/*	return (cmd);*/
/*}*/
/**/
/**/
/**/
/*int init_node_cmd(t_data *data, char **tab)*/
/*{*/
/*    int i;*/
/*    t_node_cmd *new_node;*/
/**/
/*    i = 0;*/
/*    data->cmd = ft_lstnew_cmd(tab[i], i);*/
/*    while (tab[++i])*/
/*    {*/
/*        new_node = ft_lstnew_cmd(tab[i], i);*/
/*        if (!new_node)*/
/*            return (-1);*/
/*        ft_lstadd_back_cmd(data->cmd, new_node);*/
/*		data->cmd = data->cmd->next;*/
/*    }*/
/*    return (0);*/
/*}*/
/**/

size_t	ft_count_str(char *str, char sep)
{
	size_t	i = 0;
	size_t	count = 0;

	if (!str)
		return (0);
	while (str[i])
	{
		if (i != 0 && str[i] == sep && str[i - 1] != sep)
			count++;
		i++;
	}
	if (i != 0 && str[i - 1] != sep)
		count++;
	return (count);
}

char	*ft_strtok(char	*str, char sep)
{
	static char	*ptr;
	char		*tok;
	size_t		i;

	i = 0;
	if (str)
	{
		ptr = str;
		while (*ptr == sep)
			ptr++;
	}
	else if (!ptr || !*ptr)
		return (NULL);
	while (ptr[i] && ptr[i] != sep)
		i++;
	if (ptr[i] == sep)
	{
		ptr[i] = 0;
		tok = ft_strdup(ptr);
		i++;
		while (ptr[i] && ptr[i] == sep)
			i++;
	}
	else
		tok = ft_strdup(ptr);
	ptr = &ptr[i];
	return (tok);
}

t_node_cmd	*cmd_get_content(char *str, size_t index);

char	**init_cmd(t_data *data ,char *argv)
{
	t_node_cmd	*ptr;
	char		**pips;
	size_t		i;
	char		*tok;

	i = 0;
	data->number_of_pip = ft_count_str(argv, '|') - 1;
	data->number_of_cmd = data->number_of_pip + 1;
	pips = malloc(sizeof(char *) * (data->number_of_pip + 1));
	tok = ft_strtok(argv, '|');
	while (tok)
	{
		pips[i] = tok;
		tok = ft_strtok(NULL, '|');
		i++;
	}
	pips[i] = NULL;
	i = 1;
	data->cmd = cmd_get_content(pips[0], 0);
	ptr = data->cmd;
	while (pips[i])
	{
		ptr->next = cmd_get_content(pips[i], i);
		ptr = ptr->next;
		i++;
	}
	return (NULL);
}

t_node_cmd	*cmd_get_content(char *str, size_t index)
{
	size_t	i;
	char	*tok;
	t_node_cmd *cmd;

	i = 0;
	cmd = ft_lstnew_cmd(index);
	cmd->content = malloc(sizeof(char *) * (ft_count_str(str, ' ') + 1));
	cmd->content[i] = ft_strtok(str, ' ');
	i++;
	tok = ft_strtok(NULL, ' ');
	while (tok)
	{
		cmd->content[i] = tok;
		i++;
		tok = ft_strtok(NULL, ' ');
	}
	cmd->content[i] = NULL;
	return (cmd);
}
