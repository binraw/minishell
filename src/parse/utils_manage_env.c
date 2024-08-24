// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   utils_manage_env.c                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/24 13:20:54 by rtruvelo          #+#    #+#             //
//   Updated: 2024/08/24 13:22:59 by rtruvelo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../mini/mini.h"

char	*loop_var_to_env(char *cpy, t_node_env *ptr, size_t i)
{
	while (ptr)
	{
		if (ft_strncmp(cpy, ptr->name, i + 1) == 0)
		{
			free(cpy);
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	free(cpy);
	return (NULL);
}

char	*tilde_to_home(t_data *data)
{
	t_node_env	*ptr;

	ptr = data->env_node;
	while (ptr)
	{
		if (ft_strncmp("HOME", ptr->name, 5) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return ("~");
}

int	loop_trim_env_len(t_data *data, char *str, size_t len, int quote)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		quote = manage_quotes(str[i], quote);
		if (str[i] == '$' && quote != 1)
			len += condition_trim_env_len(data, str, &i, quote);
		else if (str[i] == '~' && is_tilde_home(str[i + 1], quote))
		{
			len += ft_strlen(tilde_to_home(data));
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	condition_trim_env_len(t_data *data, char *str, size_t *i, int quote)
{
	size_t	len;

	len = 0;
	if (str[*i + 1] == '?')
	{
		len += ft_intlen(data->last_pid);
		*i = *i + 2;
	}
	else if (is_dollar_print(str[*i + 1], quote))
	{
		len++;
		*i = *i + 1;
	}
	else
		len += ft_strlen(var_to_env(&str[*i + 1], i, data));
	return (len);
}

size_t	ft_intlen(int nb)
{
	size_t	len;

	len = 0;
	if (nb < 0)
		len++;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}
