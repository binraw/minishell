/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdocs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:54:57 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/24 12:33:01 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"



// fonction a envoyer quand un rdocs est envoyer dans une commande
// meme comportetment des infiles
// f
int init_rdocs(t_rdocs *rdocs)
{
    int *fd;


setup_readline_rdocs();
    fd = malloc(2 * sizeof(int));
    if (pipe(fd) == -1)
		return (-1);
    rdocs->go = false;
    while (rdocs->go != true)
    {
        rdocs->str_rdocs = readline("> ");
		if (!rdocs->str_rdocs)
		{
			printf("bash: warning: here-document at line 2 delimited by end-of-file (wanted `wc')\n");
			return (-1);
		}
        if (ft_strncmp(rdocs->str_rdocs,
                rdocs->limit, (ft_strlen(rdocs->str_rdocs)) + 1) == 0)
        {
            free(rdocs->str_rdocs);
            rdocs->go = true;
			close(fd[1]);
            return (fd[0]);
        }
		if (interrupted == 1)
			break ;
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
			return (-1);
		dup = dup->next;	
	}
	if (last_in->rdocs)
	{
		cmd->fd_rdoc = fd;
	}
	return (0);
}


int command_rdocs(t_data *data)
{
	t_node_cmd *dup;

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
