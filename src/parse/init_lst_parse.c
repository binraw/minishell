/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:24:07 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/17 10:31:26 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

char	**init_cmd(t_data *data ,char *argv)
{
	char **cmd;
	int		y;

	y = 0;
	if (argv[y] == '\0')
		return (NULL);
	while (argv[y] == ' ')
	{
		if (argv[y + 1] == '\0')
			return (NULL);
		y++;
	}
	cmd = ft_split(argv, '|');
	init_node_cmd(data, cmd);


	
	return (cmd);
}



int init_node_cmd(t_data *data, char **tab)
{
    int i;
    t_node_cmd *new_node;

    i = 0;
    data->cmd = ft_lstnew_cmd(tab[i]);
    while (tab[++i])
    {
        new_node = ft_lstnew_cmd(tab[i]);
        if (!new_node)
            return (-1);
        ft_lstadd_back_cmd(data->cmd, new_node);
		data->cmd = data->cmd->next;
    }
    return (0);
}


int	init_lst_cmd(t_data *data, size_t i) // le i sera a partir d'ou on ecrit la nouvelle commande
{
	while (data->str[i] != '|' && data->str[i])
		i++;
	data->cmd->content = malloc(i * sizeof(char));
	if (!data->cmd)
		return (-1);
	ft_strlcpy(data->cmd->content, data->str, i);
	return (i);
}
	