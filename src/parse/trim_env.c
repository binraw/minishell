// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   trim_env.c                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/24 13:24:16 by rtruvelo          #+#    #+#             //
//   Updated: 2024/08/24 13:48:10 by rtruvelo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../mini/mini.h"

char	*trim_env(t_data *data, char *pip)
{
	char	*str;
	size_t	i;
	size_t	j;
	int		quote;
	int		len;

	i = 0;
	j = 0;
	quote = 0;
	if (is_line_empty(pip))
		return (pip);
	len = (trim_env_len(pip, data) + 1);
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_bzero(str, len);
	str = loop_trim_env(data, str, pip, quote);
	if (pip)
		free(pip);
	return (str);
}

char	*loop_trim_env(t_data *data, char *str, char *pip, int quote)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (pip[i])
	{
		quote = manage_quotes(pip[i], quote);
		if (pip[i] == '$' && quote != 1)
		{
			if (pip[i + 1] == '?')
				cpy_return_to_str(ft_itoa(data->last_pid), str, &j, &i);
			else if (is_dollar_print(pip[i + 1], quote))
				cpy_str_pip(&str, &pip, &i, &j);
			else
				cpy_env_to_str(var_to_env(&pip[i + 1], &i, data), str, &j);
		}
		else if (pip[i] == '~' && is_tilde_home(pip[i + 1], quote))
			i = cpy_env_tilde_to_home(data, str, j, &i);
		else
			cpy_str_pip(&str, &pip, &i, &j);
	}
	return (str);
}

size_t	cpy_env_tilde_to_home(t_data *data, char *str, size_t j, size_t *i)
{
	cpy_env_to_str(tilde_to_home(data), str, &j);
	*i = *i + 1;
	return (*i);
}

size_t	cpy_str_pip(char **str, char **pip, size_t *i, size_t *j)
{
	if (*str && *pip)
	{
		(*str)[*j] = (*pip)[*i];
		*i = *i + 1;
		*j = *j + 1;
		return (*i + *j);
	}
	return (0);
}

void	cpy_env_to_str(char	*env, char *str, size_t *j)
{
	size_t	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		str[*j] = env[i];
		*j = *j + 1;
		i++;
	}
}
