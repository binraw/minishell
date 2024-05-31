/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdocs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:54:57 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/31 14:24:44 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// fonction a envoyer quand un rdocs est envoyer dans une commande
// meme comportetment des infiles
int init_rdocs(t_rdocs *rdocs)
{
    int *fd;

    fd = malloc(2 * sizeof(int));
    if (pipe(fd) == -1)
		return (-1);
    rdocs->go = false;
	/*printf(" la valeur de limits :%s\n", rdocs->limit);*/
    while (rdocs->go != true)
    {
        rdocs->str_rdocs = readline("> ");	
		/*printf(" la valeur de str_rdocs :%s\n", cmd->rdocs->str_rdocs);*/
        if (ft_strncmp(rdocs->str_rdocs,
                rdocs->limit, ft_strlen(rdocs->str_rdocs)) == 0)
        {
			/*printf("ca doit se couper la le rdocs\n");*/
            free(rdocs->str_rdocs);
            rdocs->go = true;
			close(fd[1]);
            return (fd[0]);
        }
        write(fd[1], rdocs->str_rdocs, ft_strlen(rdocs->str_rdocs));
        write(fd[1], "\n", 1);
    }
    return (-1);
}


int	open_all_rdocs(t_node_cmd *cmd) // je pense pas besoin de prendre data en argument
{
	t_redir *last_in;
	t_rdocs *dup;
	int fd;

	last_in = get_last_in(cmd->redir);
	if (!last_in)
		return (0);
	dup = cmd->rdocs;
	fd = 0;
	while (dup)
	{	
	
			fd = init_rdocs(dup);
			if (fd == -1)
					return (printf("error de init r_docs"));

		dup = dup->next;
		
	}
	/*printf("last_in : %s\n", last_in->content);*/
	if (last_in->rdocs)
		{
			cmd->fd_rdoc = fd;
			/*printf("la valeur du fd : %d\n", fd);*/
		}


	return (0);
}


int command_rdocs(t_data *data)
{
	t_node_cmd *dup;
	printf("test du print\n");
	dup = data->cmd;
	while (dup)
	{
		/*printf("content dup : %s\n", dup->content[0]);*/
		/*printf("dup rdocs content : %p\n", dup->rdocs);*/
		if (dup->rdocs)
			open_all_rdocs(dup);
		dup = dup->next;
	}
	return (0);
}
