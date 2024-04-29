/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:26 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/29 13:24:50 by rtruvelo         ###   ########.fr       */
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

int ft_redir_in(t_data *data, int y)
{
    size_t i;

    i = 0;
    while (data->redir[y].tab_file_in[i])
    {
        data->redir[y].in = open(data->redir[y].tab_file_in[i], O_RDONLY, 00644);
        if (data->redir->in < 0)
            return (-1);
        i++;
    }
    data->redir->in = open(data->redir[y].tab_file_in[i - 1], O_RDONLY, 00644); // ici nous ouvrons le dernier file qui doit etre celui prit en compte dans bash
    if (data->redir[y].in < 0)
        return (-1);
    return (data->redir[y].in);
}


int ft_redir_out(t_data *data, int y)
{
    size_t i;

    i = 0;
    while (data->redir[y].tab_file_out[i])
    {
        data->redir[y].out = open(data->redir[y].tab_file_out[i], (O_CREAT | O_WRONLY | O_TRUNC), 00644);
        if (data->redir[y].out < 0)
            return (-1);
        i++;
    }
    data->redir[y].out = open(data->redir[y].tab_file_out[i - 1], (O_CREAT | O_WRONLY | O_TRUNC), 00644);
    if (data->redir[y].out < 0)
        return (-1);
    return (data->redir[y].out);
}

int ft_dup_redir_second_child(t_data *data , int **pip, int y , int i)
{
    if (2 != data->number_of_cmd && i != (data->number_of_cmd -1)
            && data->redir[i].in && !data->redir[i].out)
	{
		close(pip[y][1]);
		dup2(data->redir[i].in, STDIN_FILENO);
		close(pip[y][0]);
		dup2(pip[y + 1][1], STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(data->redir[i].in);
	}
    else if (2 != data->number_of_cmd && i != (data->number_of_cmd -1)
            && data->redir[i].in && data->redir[i].out)
	{
		close(pip[y][1]);
		dup2(data->redir[i].in, STDIN_FILENO);
		close(pip[y][0]);
		dup2(data->redir[i].out, STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(data->redir[i].in);
        close(data->redir[i].out);
	}
    else if (2 != data->number_of_cmd && i != (data->number_of_cmd -1)
        && !data->redir[i].in && data->redir[i].out)
	{
		close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		close(pip[y][0]);
		dup2(data->redir[i].out, STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(data->redir[i].in);
        close(data->redir[i].out);
	}
    else //ce cas la a regarder de pres car je sais pas si cest possible de rentrer la alors quil
    // a peut etre un out ...
    {
        close(pip[y][1]);
		dup2(data->redir[i].in, STDIN_FILENO);
		close(pip[y][0]);
        close(data->redir[i].in);
    }
   return (0);
}

int     ft_redir_child_process(t_data *data, int *pip, int i)
{
    close(pip[0]); 
	dup2(data->redir[i].out, STDOUT_FILENO);
	close(pip[1]);
    close(data->redir[i].out);
    return (0);
}
