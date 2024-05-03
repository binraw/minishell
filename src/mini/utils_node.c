/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:45:54 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/02 12:43:28 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


t_node_env	*ft_lstnew(t_data *data, char *content)
{
	(void) data;
	t_node_env	*element;
    char **line;
    int i;

    i = 0;
	element = malloc(sizeof(t_node_env));
	if (!element)
		return (NULL);
	element->content = content;
    line = ft_split(content, '=');
    if (!line)
        return (NULL);
    element->name = line[i];
    element->next = NULL;
	i = 1;
	element->value = ft_strjoin(NULL, line[i]);
    while (line[i])
    {
		element->value = ft_strjoin(element->value, "=");
		element->value = ft_strjoin(NULL, line[i]);	
		i++;
    }

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

int	ft_lstadd_back(t_node_env **lst, t_node_env *new_node)
{
	t_node_env	*last;

	if (!new_node)
		return (-1);
	if (*lst == NULL)
	{
		*lst = new_node;
		new_node->next = NULL;
		return (0);
	}
	else
	{
		last = ft_lstlast(*lst);
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
		printf("%s -> ", current->content);
		current = current->next;
	}
	printf("NULL\n");
}


t_node_env	*ft_lstduplicate(const t_node_env *original)
{
	t_node_env	*copy;
	t_node_env	*original_ptr;
	t_node_env	*copy_ptr;

	copy = ft_lstnew_basic(original->content);
	if (!copy)
		return (NULL);
	original_ptr = original->next;
	copy_ptr = copy;
	if (!original)
		return (NULL);
	while (original_ptr)
	{
		copy_ptr->next = ft_lstnew_basic(original_ptr->content);
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
