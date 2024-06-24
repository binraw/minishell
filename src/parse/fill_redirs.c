/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:51:57 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/06/24 10:49:57 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

// je remplis la liste chainee t_redir
void	fill_redirs(char *tok, t_redir **redir, t_rdocs **rdocs)
{
	t_redir	*ptr;

	*redir = init_redirs(tok, rdocs);
	ptr = *redir;
	tok = ft_strtok(NULL, " \t", true);
	while (tok)
	{
		if (*tok == '>')
		{
			if (tok[1] == '>')
				ptr->next = redir_lst_new(4, trim_redir(tok, 2));
			else
				ptr->next = redir_lst_new(2, trim_redir(tok, 1));
		}
		else if (*tok == '<')
		{
			if (tok[1] == '<')
				ptr->next = fill_rdocs(tok, rdocs);
			else
				ptr->next = redir_lst_new(1, trim_redir(tok, 1));
		}
		tok = ft_strtok(NULL, " \t", true);
		ptr = ptr->next;
	}
}

t_redir	*init_redirs(char *tok, t_rdocs **rdocs)
{
	if (*tok == '>')
	{
		if (tok[1] == '>')
			return (redir_lst_new(4, trim_redir(tok, 2)));
		else
			return (redir_lst_new(2, trim_redir(tok, 1)));
	}
	else if (*tok == '<')
	{
		if (tok[1] == '<')
			return (fill_rdocs(tok, rdocs));
		else
			return (redir_lst_new(1, trim_redir(tok, 1)));
	}
	else
		return (NULL);
}

char	*trim_redir(char *tok, int i)
{
	char	*str;
	size_t	j;

	j = i;
	while (tok[j])
		j++;
	while (j != 0 && (tok[j - 1] == ' ' || tok[j] == '\t'))
		j--;
	tok[j] = 0;
	while (tok[i] && (tok[i] == ' ' || tok[i] == '\t'))
		i++;
	str = ft_strdup(&tok[i]);
	free(tok);
	return (str);
}

t_redir	*fill_rdocs(char *tok, t_rdocs **rdocs)
{
	t_rdocs	*ptr;

	tok = trim_redir(tok, 2);
	ptr = *rdocs;
	if (!ptr)
		*rdocs = ft_lstnew_rdocs(tok);
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = ft_lstnew_rdocs(tok);
	}
	return (redir_lst_new(3, tok));
}
