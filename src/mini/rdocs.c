/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdocs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:54:57 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/29 12:37:52 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int init_rdocs(t_data *data)
{
    int *fd_rdocs;

    fd_rdocs = malloc(2 * sizeof(int));
    if (pipe(fd_rdocs) == -1)
		return (-1);
    data->rdocs->go = false;
    while (data->rdocs->go != true)
    {
        data->rdocs->str_rdocs = readline("> ");
        if (ft_strncmp(data->rdocs->str_rdocs,
                data->rdocs->limit, ft_strlen(data->rdocs->limit)))
        {
            free(data->rdocs->str_rdocs);
            data->rdocs->go = true;
            break ;
        }
        write(fd_rdocs[1], data->rdocs->str_rdocs, ft_strlen(data->rdocs->str_rdocs));
        write(fd_rdocs[1], "\n", 1);
    }
    return (fd_rdocs);
}