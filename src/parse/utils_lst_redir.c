/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:16:34 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/05/22 15:04:13 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

t_redir	*redir_lst_new(int type, char *tok)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->in = false;
	new->out = false;
	new->rdocs = false;
	new->d_out = false;
	if (type == 1)
		new->in = true;
	if (type == 2)
		new->out = true;
	if (type == 3)
		new->rdocs = true;
	if (type == 4)
		new->d_out = true;
	new->content = tok;
	new->next = NULL;
	return (new);
}

void	ft_lstclear_redir(t_redir **lst)
{
	t_redir	*current;
	t_redir	*next;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		if (current->content)
			free (current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
