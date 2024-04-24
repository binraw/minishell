/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:26 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/24 15:35:27 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_redir(t_redir *redir)
{
    redir->in = 0;
    redir->out = 1;
    // placer ici ce qui va etre le parsing des fichiers dans tab_file ou file
    return (0);
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
    redir->in = open(redir->file_in, O_RDONLY, 00644); // ici nous ouvrons le dernier file qui doit etre celui prit en compte dans bash
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

int redir_check(t_redir *redir, t_data *data)
{
    size_t i;
    size_t y;
    
    i = 0;
    y = 0;
    // il faut que je definisse la taille de tab_file
    // que jarrive a reflechir a comment faire quand il y a les deux cas
    // lancer possiblement les fonctions 
    while (data->cmd[i])
	{ 
	// la ici bizarre car il peut en avoir plusieurs par commande donc comment faire ?
    while (data->cmd[i][y])
    {
        if (data->cmd[i][y] == '>')
        {
           redir->tab_file = ft_split(data->cmd[i], '>');
            // c'est donc une redirection vers un out 
        }
        else if (data->cmd[i][y] == '<')
        {
            redir->tab_file = ft_split(data->cmd[i], '<');
            // c'est une redirection vers un in 
        }
        y++;
    }
	i++;
	}
	return (0);
}