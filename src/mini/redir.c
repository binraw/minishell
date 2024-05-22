/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:26 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/22 14:03:30 by rtruvelo         ###   ########.fr       */
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

int ft_redir_in(t_node_cmd *cmd, int y)
{
    size_t i;

    i = 0;
    while (cmd->redir[y].tab_file_in[i])
    {
        cmd->redir[y].in = open(cmd->redir[y].tab_file_in[i], O_RDONLY, 00644);
        if (cmd->redir->in < 0)
            return (-1);
        i++;
    }
    cmd->redir->in = open(cmd->redir[y].tab_file_in[i - 1], O_RDONLY, 00644); // ici nous ouvrons le dernier file qui doit etre celui prit en compte dans bash
    if (cmd->redir[y].in < 0)
        return (-1);
    return (cmd->redir[y].in);
}


int ft_redir_out(t_node_cmd *cmd, int y)
{
    size_t i;

    i = 0;
    while (cmd->redir[y].tab_file_out[i])
    {
        cmd->redir[y].out = open(cmd->redir[y].tab_file_out[i], (O_CREAT | O_WRONLY | O_TRUNC), 00644);
        if (cmd->redir[y].out < 0)
            return (-1);
        i++;
    }
    cmd->redir[y].out = open(cmd->redir[y].tab_file_out[i - 1], (O_CREAT | O_WRONLY | O_TRUNC), 00644);
    if (cmd->redir[y].out < 0)
        return (-1);
    return (cmd->redir[y].out);
}


int open_all_redir(t_node_cmd *cmd)
{
	int i;

	i = 0;	
	while (cmd->redir)
	{
		if (cmd->redir->in)
		{
			i = open(cmd->redir->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
        	if (i < 0)
            	return (-1);
		}
		else if (cmd->redir->out)
		{
			i =  open(cmd->redir->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
        	if (i < 0)
            	return (-1);
		}
		else if (cmd->redir->rdocs)
		{
			i = 0; // faire mon rdocs ici
		}
		else if (cmd->redir->d_out)
		{
			i = open(cmd->redir->content, (O_APPEND), 00644);
		}
		cmd->redir = cmd->redir->next;
	}
}
			

int ft_dup_redir_second_child(t_data *data, t_node_cmd *cmd , int **pip, int y)
{
	int i; // ici le i doit etre remplacer 
	//
	i = 0;
    if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)
            && cmd->redir[i].in && !cmd->redir[i].out)
	{
		close(pip[y][1]);
		dup2(cmd->redir[i].in, STDIN_FILENO); //remplacer ici pAR LA FONCtion qui trouve le dernier de la liste en question
		close(pip[y][0]);
		dup2(pip[y + 1][1], STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(cmd->redir[i].in);
	}
    else if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)
            && cmd->redir[i].in && cmd->redir[i].out)
	{
		close(pip[y][1]);
		dup2(cmd->redir[i].in, STDIN_FILENO);
		close(pip[y][0]);
		dup2(cmd->redir[i].out, STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(cmd->redir[i].in);
        close(cmd->redir[i].out);
	}
    else if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)
        && !cmd->redir[i].in && cmd->redir[i].out)
	{
		close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		close(pip[y][0]);
		dup2(cmd->redir[i].out, STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(cmd->redir[i].in);
        close(cmd->redir[i].out);
	}
    else //ce cas la a regarder de pres car je sais pas si cest possible de rentrer la alors quil
    // a peut etre un out ...
    {
        close(pip[y][1]);
		dup2(cmd->redir[i].in, STDIN_FILENO);
		close(pip[y][0]);
        close(cmd->redir[i].in);
    }
   return (0);
}

int     ft_redir_child_process(t_node_cmd *cmd, int *pip)
{
	int i; // le i est temporaire doit etre changer
	
	i = 0;
    close(pip[0]); 
	dup2(cmd->redir[i].out, STDOUT_FILENO);
	close(pip[1]);
    close(cmd->redir[i].out);
    return (0);
}
