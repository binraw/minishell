/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:05:55 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/09 11:55:52 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*newcontent;
	t_list	*newlst;
	t_list	*temp;

	current = lst;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	newlst = NULL;
	while (current != NULL)
	{
		temp = f(current->content);
		newcontent = ft_lstnew(temp);
		if (!newcontent)
		{
			ft_lstclear(&newlst, del);
			del(temp);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newcontent);
		current = current->next;
	}
	return (newlst);
}

