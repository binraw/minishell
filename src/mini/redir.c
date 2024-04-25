/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:26 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/25 14:08:12 by rtruvelo         ###   ########.fr       */
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
    if (dara->redir->in < 0)
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

// int redir_check(t_redir *redir, t_data *data)
// {
//     size_t i;
//     size_t y;
    
//     i = 0;
//     y = 0;
//     // il faut que je definisse la taille de tab_file
//     // que jarrive a reflechir a comment faire quand il y a les deux cas
//     // lancer possiblement les fonctions 
//     while (data->cmd[i])
// 	{ 
// 	// la ici bizarre car il peut en avoir plusieurs par commande donc comment faire ?
//     while (data->cmd[i][y])
//     {
//         if (data->cmd[i][y] == '>')
//         {
//            redir->tab_file = ft_split(data->cmd[i], '>');
//             // c'est donc une redirection vers un out 
//         }
//         else if (data->cmd[i][y] == '<')
//         {
//             redir->tab_file = ft_split(data->cmd[i], '<');
//             // c'est une redirection vers un in 
//         }
//         y++;
//     }
// 	i++;
// 	}
// 	return (0);
// }