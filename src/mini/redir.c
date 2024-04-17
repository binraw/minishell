/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:26 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/17 12:34:47 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_redir(t_redir *redir)
{
    redir->in = 0;
    redir->out = 1;
    // placer ici ce qui va etre le parsing des fichiers dans tab_file ou file
}

int ft_redir_in(t_redir *redir)
{
    size_t i;

    i = 0;
    while (redir->tab_file[i])
    {
        redir->in = open(redir->tab_file[i], O_RDONLY, 00644);
        if (redir->in < 0)
            return (-1); // ca veut dire qu un des fichier en lecture est mauvais donc erreur 
        i++;
    }
    redir->in = open(redir->file, O_RDONLY, 00644); // ici nous ouvrons le dernier file qui doit etre celui prit en compte dans bash
    if (redir->in < 0)
        return (-1);
    return (redir->in);
}

int ft_redir_out(t_redir *redir)
{
    redir->out = open(redir->file_out, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
    if (redir->out < 0)
        return (-1);
    return (redir->out);
}