/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdocs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:54:57 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/30 10:55:08 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_rdocs(t_rdocs *rdocs, int *fd)
{
	write(fd[1], rdocs->str_rdocs, ft_strlen(rdocs->str_rdocs));
	write(fd[1], "\n", 1);
	free(rdocs->str_rdocs);
}

int	rdocs_error(int *fd)
{
	free(fd);
	ft_putstr_fd("bash: warning: here-document at line 2 delimited", 2);
	ft_putstr_fd("by end-of-file (wanted `wc')\n", 2);
	return (-1);
}

int	stop_success_rdocs(t_rdocs *rdocs, int *fd)
{
	int	fd_in;

	rdocs->go = true;
	close(fd[1]);
	fd_in = fd[0];
	free(fd);
	return (fd_in);
}
