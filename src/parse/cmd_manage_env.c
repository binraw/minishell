/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manage_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:10:26 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/05/31 09:23:07 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

void	cmd_manage_env(t_data *data, char **pips)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = 0;
	j = 0;
	// printf("aled\n");
	while (pips[i])
	{
		j = 0;
		quote = 0;
		while (pips[i][j])
		{
			quote = manage_quotes(pips[i][j], quote);
			if (pips[i][j] == '$' && quote != 1)
			{
				pips[i] = trim_env(data, pips[i]);
				// printf("pips = %s\n", pips[i]);
				break ;
			}
			j++;
		}
		i++;
	}
}

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
	len = (trim_env_len(pip, data) + 1);
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_bzero(str, len);
	while (pip[i])
	{
		quote = manage_quotes(pip[i], quote);
		if (pip[i] == '$' && quote != 1)
			cpy_env_to_str(var_to_env(&pip[i + 1], &i, data), str, &j);
		else
		{
			str[j] = pip[i];
			// printf("pip2 = %s\nstr = %s\n", &pip[i], str);
			i++;
			j++;
		}
	}
	if (pip)
		free(pip);
	return (str);
}

void	cpy_env_to_str(char	*env, char *str, size_t *j)
{
	size_t	i;

	i = 0;
	// printf("env = %s\n", env);
	if (!env)
		return ;
	while (env[i])
	{
		str[*j] = env[i];
		*j = *j + 1;
		i++;
	}
}

size_t	trim_env_len(char *str, t_data *data)
{
	size_t	i;
	size_t	len;
	int		quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		quote = manage_quotes(str[i], quote);
		// printf("%s\n", &str[i]);
		if (str[i] == '$' && quote != 1)
			len += ft_strlen(var_to_env(&str[i + 1], &i, data));
		else
		{
			len++;
			i++;
		}
	}
	return (len);
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
	if (i <= 1)
		return (NULL);
	cpy = malloc(sizeof(char) * (i + 1));
	// printf("var to env %s\n", str);
	i = ft_strlcpy(cpy, str, i + 1);
	// printf("cpy = %s\n", cpy);
	ptr = data->env_node;
	while (ptr)
	{
		if (ft_strncmp(cpy, ptr->name, i) == 0)
		{
			free(cpy);
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	free(cpy);
	return (NULL);
}
