/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:12:31 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/29 11:05:30 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./mini.h"

t_node_cmd	*ft_lstnew_cmd(int i)
{
	t_node_cmd	*element;

	element = malloc(sizeof(t_node_cmd));
	if (!element)
		return (NULL);
	element->content = NULL;
	element->index = i;
	element->next = NULL;
	element->redir = NULL;
	element->rdocs = NULL;
	element->fd_rdoc = 0;
	return (element);
}

t_rdocs	*ft_lstnew_rdocs(char *str)
{
	t_rdocs	*ptr;

	ptr = malloc(sizeof(t_rdocs));
	if (!ptr)
		return (NULL);
	ptr->limit = ft_strdup(str);
	ptr->str_rdocs = NULL;
	ptr->go = false;
	ptr->next = NULL;
	return (ptr);
}

t_node_cmd	*ft_lstlast_cmd(t_node_cmd *lst)
{
	t_node_cmd	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

int	ft_lstadd_back_cmd(t_node_cmd *lst, t_node_cmd *new_node)
{
	t_node_cmd	*last;

	if (!new_node)
		return (-1);
	if (lst == NULL)
	{
		lst = new_node;
		new_node->next = NULL;
		return (0);
	}
	else
	{
		last = ft_lstlast_cmd(lst);
		last->next = new_node;
		new_node->index = last->index + 1;
	}
	return (0);
}

void	ft_lstclear_cmd(t_node_cmd **lst)
{
	t_node_cmd	*current;
	t_node_cmd	*next;
	size_t		i;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		i = 0;
		next = current->next;
		if (current->content)
		{
			while (current->content[i])
			{
				free(current->content[i]);
				i++;
			}
			free (current->content[i]);
			free (current->content);
		}
		if (current->redir)
			ft_lstclear_redir(&current->redir);
		if (current->rdocs)
			ft_lstclear_rdocs(&current->rdocs);
		free(current);
		current = next;
	}
	*lst = NULL;
}

