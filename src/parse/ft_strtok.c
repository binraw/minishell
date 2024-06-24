/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:16:27 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/06/18 15:46:08 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

// je decoupe la string avec des separateurs a la facon d'un GNL
char	*ft_strtok(char	*str, char *sep, bool redir)
{
	static char	*ptr;
	char		*tok;
	size_t		i;

	i = 0;
	if (str)
	{
		ptr = str;
		if (!sep)
			return (ft_strdup(str));
		while (ft_strchr(sep, *ptr))
			ptr++;
	}
	else if (!ptr || !*ptr)
		return (NULL);
	else if (!sep)
		return (ft_strdup(ptr));
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

char	*create_tok(char *sep, char *ptr, bool redir, size_t *i)
{
	int		quote;
	char	*tok;

	quote = 0;
	while (ptr[*i] && (!ft_strchr(sep, ptr[*i]) || quote != 0))
	{
		if (ptr[*i] == '\'' || ptr[*i] == '\"')
			quote = manage_quotes(ptr[*i], quote);
		if (quote == 0 && redir && (ptr[*i] == '<' || ptr[*i] == '>'))
			break ;
		*i = *i + 1;
	}
	if (quote == 0 && redir && (ptr[*i] == '<' || ptr[*i] == '>'))
		tok = tok_stop_redir(ptr, i);
	else if (ptr[*i] && ft_strchr(sep, ptr[*i]) && quote == 0)
	{
		ptr[*i] = 0;
		tok = ft_strdup(ptr);
		*i = *i + 1;
		while (ptr[*i] && ft_strchr(sep, ptr[*i]))
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
	while (str[*i] == ' ' || str[*i] == '\t')
		*i = *i + 1;
	while (str[*i] && ((str[*i] != '<' && str[*i] != '>') || quote != 0))
	{
		if (quote == 0 && str[*i] == ' ')
			break ;
		if (str[*i] == '\'' || str[*i] == '\"')
			quote = manage_quotes(str[*i], quote);
		*i = *i + 1;
	}
	tok = tok_stop_redir(str, i);
	return (tok);
}

// j'arrete strtok quand je trouve '>' ou '<'
char	*tok_stop_redir(char *str, size_t *i)
{
	char	c;
	char	*tok;

	c = str[*i];
	str[*i] = 0;
	tok = ft_strdup(str);
	if (c == ' ' || c == '\t')
		*i = *i + 1;
	else
		str[*i] = c;
	return (tok);
}
