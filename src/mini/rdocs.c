/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdocs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:54:57 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/29 15:30:32 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// fonction a envoyer quand un rdocs est envoyer dans une commande
// meme comportetment des infiles
int init_rdocs(t_node_cmd *cmd)
{
    int *fd;

    fd = malloc(2 * sizeof(int));
    if (pipe(fd) == -1)
		return (-1);
    cmd->rdocs->go = false;
	/*printf(" la valeur de limits :%s\n", cmd->rdocs->limit);*/
    while (cmd->rdocs->go != true)
    {
        cmd->rdocs->str_rdocs = readline("> ");	
		/*printf(" la valeur de str_rdocs :%s\n", cmd->rdocs->str_rdocs);*/
        if (ft_strncmp(cmd->rdocs->str_rdocs,
                cmd->rdocs->limit, ft_strlen(cmd->rdocs->str_rdocs)) == 0)
        {
			/*printf("ca doit se couper la le rdocs\n");*/
            free(cmd->rdocs->str_rdocs);
            cmd->rdocs->go = true;
			close(fd[1]);
            return (fd[0]);
        }
        write(fd[1], cmd->rdocs->str_rdocs, ft_strlen(cmd->rdocs->str_rdocs));
        write(fd[1], "\n", 1);
    }
    return (-1);
}


int	open_all_rdocs(t_node_cmd *cmd) // je pense pas besoin de prendre data en argument
{
	t_redir *last_in;
	t_redir *dup;
	int fd;

	last_in = get_last_in(cmd->redir);
	dup = cmd->redir;
	fd = 0;	
	while (dup)
	{	
		if (dup->rdocs)
		{
			//jimagine un open peut etre avec seulement un o-write pour recuperer un fd et l'envoyer dedans et le recup par la suite
			fd = init_rdocs(cmd);
			if (fd == -1)
					return (printf("error de init r_docs"));
			if (get_last_in(cmd->redir)) // je regarde si il est dernier des in si oui alors je recupere son fd de lecture pour le renvoyer
			{
				/*printf("le fd est bien transferer\n");*/
				cmd->fd_rdoc = fd;
			}
		}
		dup = dup->next;
		
	}
	return (0);
}
