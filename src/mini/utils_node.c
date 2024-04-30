/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:45:54 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/30 11:32:08 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


t_node_env	*ft_lstnew(char *value)
{
	t_node_env	*element;

	element = malloc(sizeof(t_node_env));
	if (!element)
		return (NULL);
	element->value = value;
	element->next = NULL;
	return (element);
}

t_node_env	*ft_lstlast(t_node_env *lst)
{
	t_node_env	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

int	ft_lstadd_back(t_node_env **lst, t_node_env *new)
{
	t_node_env	*last;

	if (!new)
		return (-1);
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return (0);
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	return (0);
}

void	print_liste(t_node_env *liste)
{
	t_node_env	*current;

	if (liste == NULL)
	{
		printf("NULL\n");
	}
	current = liste;
	while (current != NULL)
	{
		printf("%s -> ", current->value);
		current = current->next;
	}
	printf("NULL\n");
}
