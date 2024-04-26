/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:26 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/26 11:45:25 by rtruvelo         ###   ########.fr       */
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

int ft_redir_in(t_data *data)
{
    size_t i;

    i = 0;
    while (data->redir->tab_file_in[i])
    {
        data->redir->in = open(data->redir->tab_file_in[i], O_RDONLY, 00644);
        if (data->redir->in < 0)
            return (-1);
        i++;
    }
    data->redir->in = open(data->redir->tab_file_in[i - 1], O_RDONLY, 00644); // ici nous ouvrons le dernier file qui doit etre celui prit en compte dans bash
    if (data->redir->in < 0)
        return (-1);
    return (data->redir->in);
}


int ft_redir_out(t_data *data)
{
     size_t i;

    i = 0;
    while (data->redir->tab_file_out[i])
    {
        data->redir->out = open(data->redir->tab_file_out[i], (O_CREAT | O_WRONLY | O_TRUNC), 00644);
        if (data->redir->out < 0)
            return (-1);
        i++;
    }
    data->redir->out = open(data->redir->tab_file_out[i - 1], (O_CREAT | O_WRONLY | O_TRUNC), 00644);
    if (data->redir->out < 0)
        return (-1);
    return (data->redir->out);
}

int ft_dup_redir_second_child(t_data *data , int **pip, int y , int i)
{
    if (2 != data->number_of_cmd && i != (data->number_of_cmd -1)
            && data->redir->file_in && !data->redir->file_out)
	{
		close(pip[y][1]);
		dup2(data->redir->in, STDIN_FILENO);
		close(pip[y][0]);
		dup2(pip[y + 1][1], STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(data->redir->in);
	}
    else if (2 != data->number_of_cmd && i != (data->number_of_cmd -1)
            && data->redir->file_in && data->redir->file_out)
	{
		close(pip[y][1]);
		dup2(data->redir->in, STDIN_FILENO);
		close(pip[y][0]);
		dup2(data->redir->out, STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(data->redir->in);
        close(data->redir->out);
	}
    else if (2 != data->number_of_cmd && i != (data->number_of_cmd -1)
        && !data->redir->file_in && data->redir->file_out)
	{
		close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		close(pip[y][0]);
		dup2(data->redir->out, STDOUT_FILENO);
		close(pip[y + 1][1]);
    	close(pip[y + 1][0]);
        close(data->redir->in);
        close(data->redir->out);
	}
    else //ce cas la a regarder de pres car je sais pas si cest possible de rentrer la alors quil
    // a peut etre un out ...
    {
        close(pip[y][1]);
		dup2(data->redir->in, STDIN_FILENO);
		close(pip[y][0]);
        close(data->redir->in);
    }
   return (0);
}
