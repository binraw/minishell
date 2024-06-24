/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_get_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:25:42 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/06/18 15:19:01 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

// les fonctions pour recup les derniers de chaque type

t_redir	*get_last_in(t_redir *redir)
{
	t_redir	*ptr;
	t_redir	*last;

	ptr = redir;
	last = NULL;
	while (ptr)
	{
		if (ptr->in || ptr->rdocs)
			last = ptr;
		ptr = ptr->next;
	}
	return (last);
}

t_redir	*get_last_out(t_redir *redir)
{
	t_redir	*ptr;
	t_redir	*last;

	ptr = redir;
	last = NULL;
	while (ptr)
	{
		if (ptr->out || ptr->d_out)
			last = ptr;
		ptr = ptr->next;
	}
	return (last);
}

t_redir *redir_get_last(t_redir *redir)
{
	t_redir	*ptr;

	ptr = redir;
	if (!ptr)
		return (NULL);
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	return (ptr);
}
