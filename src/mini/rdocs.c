/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdocs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:54:57 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/28 11:55:41 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// fonction a envoyer quand un rdocs est envoyer dans une commande
// meme comportetment des infiles
int init_rdocs(t_node_cmd *cmd)
{
    int *fd_rdocs;

    fd_rdocs = malloc(2 * sizeof(int));
    if (pipe(fd_rdocs) == -1)
		return (-1);
    cmd->rdocs->go = false;
    while (cmd->rdocs->go != true)
    {
        cmd->rdocs->str_rdocs = readline("> ");
        if (ft_strncmp(cmd->rdocs->str_rdocs,
                cmd->rdocs->limit, ft_strlen(cmd->rdocs->limit)))
        {
            free(cmd->rdocs->str_rdocs);
            cmd->rdocs->go = true;
            return (fd_rdocs[0]);
        }
        write(fd_rdocs[1], cmd->rdocs->str_rdocs, ft_strlen(cmd->rdocs->str_rdocs));
        write(fd_rdocs[1], "\n", 1);
    }
    return (-1);
}


int	open_all_rdocs(t_data *data, t_node_cmd *cmd) // je pense pas besoin de prendre data en argument
{
	t_redir *last_out;
	t_redir *dup;

	last_in = get_last_in(cmd->redir);
	dup = cmd->redir;

	fd = 0;	
	while (dup)
	{
		if (dup->in)
		{	
			if (dup->rdocs)
		{
			//jimagine un open peut etre avec seulement un o-write pour recuperer un fd et l'envoyer dedans et le recup par la suite
			fd = init_rdocs(data, cmd)
			if (get_last_in(cmd->redir)) // je regarde si il est dernier des in si oui alors je recupere son fd de lecture pour le renvoyer
			{
				cmd->fd_rdocs = fd;
			}
		}
		dup = dup->next;
	}

	
	return (0);
	}
}
