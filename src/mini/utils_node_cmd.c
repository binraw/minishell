/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:12:31 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/16 10:33:36 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./mini.h"

t_node_cmd	*ft_lstnew_cmd(char *content, int i)
{
	t_node_cmd	*element;
    char **line;
    int i;

    i = 0;
	element = malloc(sizeof(t_node_env));
	if (!element)
		return (NULL);
	element->content = content;
	element->index = i; 
	element->next = NULL;
	return (element);
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
	}
	return (0);
}

void	ft_lstclear_cmd(t_node_cmd **lst, void (*del)(void *))
{
	t_node_cmd	*current;
	t_node_cmd	*next;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

