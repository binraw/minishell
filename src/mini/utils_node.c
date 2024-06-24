/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:45:54 by rtruvelo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/31 11:45:08 by hbouyssi         ###   ########.fr       */
=======
/*   Updated: 2024/05/15 15:41:45 by rtruvelo         ###   ########.fr       */
>>>>>>> exec
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


t_node_env	*ft_lstnew(char *content)
{
	t_node_env	*element;
    char *line;
    int i;

    i = 0;
	element = malloc(sizeof(t_node_env));
	if (!element)
		return (NULL);
	element->content = content;
	line = ft_strdup(content);
    element->name = ft_strtok(line, "=", false);;
    element->next = NULL;
	element->print = false;
	i = 1;
	element->value = ft_strtok(NULL, NULL, false);
	free(line);
	return (element);
}

t_node_env	*ft_lstnew_basic(char *content)
{
	t_node_env	*element;

	element = malloc(sizeof(t_node_env));
	if (!element)
		return (NULL);
	element->content = content;
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

int	ft_lstadd_back(t_node_env *lst, t_node_env *new_node)
{
	t_node_env	*last;

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
		last = ft_lstlast(lst);
		last->next = new_node;
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
		printf("%s -> \n", current->content);
		current = current->next;
	}
	printf("NULL\n");
}


t_node_env	*ft_lstduplicate(const t_node_env *original)
{
	t_node_env	*copy;
	t_node_env	*original_ptr;
	t_node_env	*copy_ptr;

	copy = ft_lstnew(original->content);
	if (!copy)
		return (NULL);
	original_ptr = original->next;
	copy_ptr = copy;
	if (!original)
		return (NULL);
	while (original_ptr)
	{
		copy_ptr->next = ft_lstnew(original_ptr->content);
		if (!copy_ptr->next)
		{
			ft_lstclear(&copy, free);
			return (NULL);
		}
		copy_ptr = copy_ptr->next;
		original_ptr = original_ptr->next;
	}
	return (copy);
}

void	ft_lstclear(t_node_env **lst, void (*del)(void *))
{
	t_node_env	*current;
	t_node_env	*next;

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

