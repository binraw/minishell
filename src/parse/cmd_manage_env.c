/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manage_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:10:26 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/08/01 10:58:08 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

bool	is_dollar_print(char c, int quote)
{
	if (ft_isalpha(c) || c == '_')
		return (false);
	if (quote == 0 && (c == '\"' || c == '\''))
		return (false);
	return (true);
}

bool	is_tilde_home(char c, int quote)
{
	if (quote != 0)
		return (false);
	if (ft_is_whitespace(c) || c == '\0' || c == '|')
		return (true);
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

void	cpy_return_to_str(char	*nb, char *str, size_t *j, size_t *k)
{
	size_t	i;

	i = 0;
	if (!nb)
		return ;
	while (nb[i])
	{
		str[*j] = nb[i];
		*j = *j + 1;
		i++;
	}
	*k = *k + 2;
	free(nb);
}

size_t	trim_env_len(char *str, t_data *data)
{
	size_t	i;
	size_t	len;
	int		quote;

	i = 0;
	len = 0;
	quote = 0;
	return (loop_trim_env_len(data, str, len, quote));
}

char	*var_to_env(char *str, size_t *index, t_data *data)
{
	size_t		i;
	char		*cpy;
	t_node_env	*ptr;

	i = 0;
	if (!str || !*str)
		return (NULL);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	*index = *index + i + 1;
	if (i < 1)
		return (NULL);
	cpy = malloc(sizeof(char) * (i + 1));
	i = ft_strlcpy(cpy, str, i + 1);
	ptr = data->env_node;
	return (loop_var_to_env(cpy, ptr, i));
}
