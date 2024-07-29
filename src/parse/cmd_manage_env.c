/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manage_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:10:26 by hbouyssi          #+#    #+#             */
/*   Updated: 2024/07/29 14:05:51 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

// void	cmd_manage_env(t_data *data)
// {
// 	size_t		i;
// 	t_node_cmd	*ptr;
// 	t_redir		*r_ptr;

// 	ptr = data->cmd;
// 	while (ptr)
// 	{
// 		i = 0;
// 		while (ptr->content[i])
// 		{
// 			ptr->content[i] = trim_env(data, ptr->content[i]);
// 			i++;
// 		}
// 		r_ptr = ptr->redir;
// 		while (r_ptr)
// 		{
// 			r_ptr->content = trim_env(data, r_ptr->content);
// 			r_ptr = r_ptr->next;
// 		}
// 		ptr = ptr->next;
// 	}
// }

void	redir_manage_env(t_data *data, t_redir *redir)
{
	t_redir		*r_ptr;

	r_ptr = redir;
	while (r_ptr)
	{
		r_ptr->content = trim_env(data, r_ptr->content);
		r_ptr = r_ptr->next;
	}
}

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
		{
			if (pip[i + 1] == '?')
			{
				cpy_return_to_str(ft_itoa(data->last_pid), str, &j);
				i += 2;
			}
			else if (is_dollar_print(pip[i + 1], quote))
			{
				str[j] = pip[i];
				i++;
				j++;
			}
			else
				cpy_env_to_str(var_to_env(&pip[i + 1], &i, data), str, &j);
		}
		else if (pip[i] == '~' && is_tilde_home(pip[i + 1], quote))
		{
			cpy_env_to_str(tilde_to_home(data), str, &j);
			i++;
		}
		else
		{
			str[j] = pip[i];
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
	if (!env)
		return ;
	while (env[i])
	{
		str[*j] = env[i];
		*j = *j + 1;
		i++;
	}
}

void	cpy_return_to_str(char	*nb, char *str, size_t *j)
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
	free(nb);
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
		if (str[i] == '$' && quote != 1)
		{
			if (str[i + 1] == '?')
			{
				len += ft_intlen(data->last_pid);
				i += 2;
			}
			else if (is_dollar_print(str[i + 1], quote))
			{
				len++;
				i++;
			}
			else
				len += ft_strlen(var_to_env(&str[i + 1], &i, data));
		}
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
