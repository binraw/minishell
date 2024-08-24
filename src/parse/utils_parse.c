// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   utils_parse.c                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/24 13:30:43 by rtruvelo          #+#    #+#             //
//   Updated: 2024/08/24 13:33:34 by rtruvelo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../mini/mini.h"

void	loop_cmd_get_content(t_node_cmd *cmd, char *tok)
{
	size_t	i;

	i = 0;
	while (tok)
	{
		cmd->content[i] = tok;
		i++;
		tok = ft_strtok(NULL, " \t\n\v\f\r", true);
	}
	cmd->content[i] = NULL;
}

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

char	*loop_trim_quote(char *trim, char *str, size_t i, size_t j)
{
	int	quote;

	quote = 0;
	while (str[i])
	{
		if (quote != manage_quotes(str[i], quote))
		{
			quote = manage_quotes(str[i], quote);
			i++;
		}
		else
		{
			trim[j] = str[i];
			i++;
			j++;
		}
	}
	trim[j] = 0;
	free(str);
	return (trim);
}
