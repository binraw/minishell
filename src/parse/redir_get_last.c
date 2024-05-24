/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_get_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:25:42 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/05/22 14:32:32 by hbouyssi         ###   ########.fr       */
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
		if (ptr->in == true)
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
		if (ptr->out == true)
			last = ptr;
		ptr = ptr->next;
	}
	return (last);
}

t_redir	*get_last_rdocs(t_redir *redir)
{
	t_redir	*ptr;
	t_redir	*last;

	ptr = redir;
	last = NULL;
	while (ptr)
	{
		if (ptr->rdocs == true)
			last = ptr;
		ptr = ptr->next;
	}
	return (last);
}

t_redir	*get_last_d_out(t_redir *redir)
{
	t_redir	*ptr;
	t_redir	*last;

	ptr = redir;
	last = NULL;
	while (ptr)
	{
		if (ptr->d_out == true)
			last = ptr;
		ptr = ptr->next;
	}
	return (last);
}
