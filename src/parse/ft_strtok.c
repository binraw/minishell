/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:16:27 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/05/24 13:20:52 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

// je decoupe la string avec des separateurs a la facon d'un GNL
char	*ft_strtok(char	*str, char sep, bool redir)
{
	static char	*ptr;
	char		*tok;
	size_t		i;

	i = 0;
	if (str)
	{
		ptr = str;
		while (*ptr == sep)
			ptr++;
	}
	else if (!ptr || !*ptr)
		return (NULL);
	if (redir && (*ptr == '>' || *ptr == '<'))
	{
		tok = tok_redir(ptr, &i);
		ptr = &ptr[i];
		return (tok);
	}
	tok = create_tok(sep, ptr, redir, &i);
	ptr = &ptr[i];
	return (tok);
}

char	*create_tok(char sep, char *ptr, bool redir, size_t *i)
{
	int		quote;
	char	*tok;

	quote = 0;
	while (ptr[*i] && (ptr[*i] != sep || quote != 0))
	{
		if (ptr[*i] == '\'' || ptr[*i] == '\"')
			quote = manage_quotes(ptr[*i], quote);
		if (quote == 0 && redir && (ptr[*i] == '<' || ptr[*i] == '>'))
			break ;
		*i = *i + 1;
	}
	if (quote == 0 && redir && (ptr[*i] == '<' || ptr[*i] == '>'))
		tok = tok_stop_redir(ptr, *i);
	else if (ptr[*i] == sep && quote == 0)
	{
		ptr[*i] = 0;
		tok = ft_strdup(ptr);
		*i = *i + 1;
		while (ptr[*i] && ptr[*i] == sep)
			*i = *i + 1;
	}
	else
		tok = ft_strdup(ptr);
	return (tok);
}

// strtok les redirections
char	*tok_redir(char *str, size_t *i)
{
	char	*tok;
	int		quote;

	*i = 0;
	quote = 0;
	while (str[*i] == '<' || str[*i] == '>')
		*i = *i + 1;
	while (str[*i] && ((str[*i] != '<' && str[*i] != '>') || quote != 0))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			quote = manage_quotes(str[*i], quote);
		*i = *i + 1;
	}
	tok = tok_stop_redir(str, *i);
	return (tok);
}

// j'arrete strtok quand je trouve '>' ou '<'
char	*tok_stop_redir(char *str, size_t i)
{
	char	c;
	char	*tok;

	c = str[i];
	str[i] = 0;
	tok = ft_strdup(str);
	str[i] = c;
	return (tok);
}
