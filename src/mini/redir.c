/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:26 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/27 15:34:36 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// int init_redir(t_redir *redir)
// {
//     redir->in = 0;
//     redir->out = 1;
//     // placer ici ce qui va etre le parsing des fichiers dans tab_file ou file
//     return (0);
// }

/*int ft_redir_in(t_node_cmd *cmd, int y)*/
/*{*/
/*    size_t i;*/
/**/
/*    i = 0;*/
/*    while (cmd->redir[y].tab_file_in[i])*/
/*    {*/
/*        cmd->redir[y].in = open(cmd->redir[y].tab_file_in[i], O_RDONLY, 00644);*/
/*        if (cmd->redir->in < 0)*/
/*            return (-1);*/
/*        i++;*/
/*    }*/
/*    cmd->redir->in = open(cmd->redir[y].tab_file_in[i - 1], O_RDONLY, 00644); // ici nous ouvrons le dernier file qui doit etre celui prit en compte dans bash*/
/*    if (cmd->redir[y].in < 0)*/
/*        return (-1);*/
/*    return (cmd->redir[y].in);*/
/*}*/


/*int ft_redir_out(t_node_cmd *cmd, int y)*/
/*{*/
/*    size_t i;*/
/**/
/*    i = 0;*/
/*    while (cmd->redir[y].tab_file_out[i])*/
/*    {*/
/*        cmd->redir[y].out = open(cmd->redir[y].tab_file_out[i], (O_CREAT | O_WRONLY | O_TRUNC), 00644);*/
/*        if (cmd->redir[y].out < 0)*/
/*            return (-1);*/
/*        i++;*/
/*    }*/
/*    cmd->redir[y].out = open(cmd->redir[y].tab_file_out[i - 1], (O_CREAT | O_WRONLY | O_TRUNC), 00644);*/
/*    if (cmd->redir[y].out < 0)*/
/*        return (-1);*/
/*    return (cmd->redir[y].out);*/
/*}*/


int open_all_redir(t_node_cmd *cmd)
{
	int i;
	t_redir *last_in;
	t_redir *last_out;
	t_redir *dup;

	last_in = get_last_in(cmd->redir);
	last_out = get_last_out(cmd->redir);
	dup = cmd->redir;

	i = 0;	
	while (dup)
	{
		if (dup->in)
		{	
			if (dup != last_in)
			{
			i = open(dup->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
        	if (i < 0)
            	return (-1);
			close(i);
			}
		}
		else if (dup->out)
		{
			if (dup != last_out)
			{
			i =  open(dup->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
        	if (i < 0)
            	return (-1);	
			close(i);
			}
		}
		else if (dup->rdocs)
		{
			i = 0; // faire mon rdocs ici
		}
		else if (dup->d_out)
		{
			i = open(dup->content, (O_APPEND), 00644);
			close(i);
		}
		dup = dup->next;
	}
	return (0);
}


			

int ft_dup_redir_second_child(t_data *data, t_node_cmd *cmd , int **pip, int y)
{
	int fd_in;
	int fd_out;


	open_all_redir(cmd);
	
	if (get_last_in(cmd->redir))
	{
		printf(" value de la redir_in :%s\n", cmd->redir->content);

			fd_in = open(get_last_in(cmd->redir)->content , (O_RDONLY), 00644);
		if (fd_in <= 0)
			exit(-1);
	}
	if (get_last_out(cmd->redir))
	{
		if (cmd->redir->d_out)
			fd_out = open(get_last_in(cmd->redir)->content, (O_APPEND), 00644);
		else
			fd_out = open(get_last_out(cmd->redir)->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
	}
    if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)
            && get_last_in(cmd->redir) && !(get_last_out(cmd->redir)))
	{
		close(pip[y][1]);
		dup2(fd_in, STDIN_FILENO);
		close(pip[y][0]);
		dup2(pip[y + 1][1], STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(fd_in);
	}
    else if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)
            && get_last_in(cmd->redir) && get_last_out(cmd->redir))
	{
		close(pip[y][1]);		
		dup2(fd_in, STDIN_FILENO);
		close(pip[y][0]);
		dup2(fd_out, STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(fd_in);
        close(fd_out);
	}
    else if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)
        && !(get_last_in(cmd->redir)) && get_last_out(cmd->redir))
	{
		close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		close(pip[y][0]);
		dup2(fd_out, STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(fd_in);
        close(fd_out);
	}
    else //ce cas la a regarder de pres car je sais pas si cest possible de rentrer la alors quil
    // a peut etre un out ...
    {
        close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);  //javais mis de base fd_in
		close(pip[y][0]);
        close(fd_out);
    }
   return (0);
}

int     ft_redir_child_process(t_node_cmd *cmd, int *pip)
{
	int fd_out;
	int fd_in;

	if (get_last_out(cmd->redir))
	{
		fd_out = open(get_last_out(cmd->redir)->content, (O_CREAT | O_WRONLY | O_TRUNC), 00664);
    	close(pip[0]);
		dup2(fd_out, STDOUT_FILENO);
		close(pip[1]);
    	close(fd_out);
	}
	else if (get_last_in(cmd->redir))
	{
		fd_in = open(get_last_in(cmd->redir)->content, (O_RDONLY), 00664);
    	close(pip[0]);
		dup2(fd_in, STDIN_FILENO);
		close(pip[1]);
    	close(fd_in);
	}

    return (0);
}


int		ft_redir_one_process(t_node_cmd *cmd)
{
	int fd_out;
	int	fd_in;

	open_all_redir(cmd);
	if (get_last_in(cmd->redir))
	{
		fd_in = open(get_last_in(cmd->redir)->content , (O_RDONLY), 00644);
		if (fd_in <= 0)
			exit(-1);
	}
	if (get_last_out(cmd->redir))
		fd_out = open(get_last_out(cmd->redir)->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);

	if (!(get_last_in(cmd->redir)) && get_last_out(cmd->redir))
	{
		dup2(fd_out, STDOUT_FILENO);
    	close(fd_out);
	}
	else if (get_last_in(cmd->redir) && !(get_last_out(cmd->redir)))
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
	}

    return (0);
}
	
