/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:32 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/24 10:38:05 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int	command_echo(t_node_cmd *cmd, int fd)
{
	size_t	i;
	size_t	j;
	bool	arg;

	i = 1;
	j = 0;
	if (fd == 0)
		fd = 1;
	arg = check_echo_arg(cmd, &i, j);
	while (cmd->content[i])
	{
		ft_putstr_fd(cmd->content[i], fd);
		i++;
		if (cmd->content[i])
			ft_putchar_fd(' ', fd);
	}
	if (arg == false)
		ft_putstr_fd("\n", fd);
	return (0);
}

bool	check_echo_arg(t_node_cmd *cmd, size_t *i, size_t j)
{
	bool	arg;

	arg = false;
	while (cmd->content[*i])
	{
		if (cmd->content[*i][0] == '-')
		{
			j = 1;
			while (cmd->content[*i][j - 1])
			{
				if (!cmd->content[*i][j] && j > 1)
					arg = true;
				else if (cmd->content[*i][j] != 'n')
					return (arg);
				j++;
			}
		}
		else
			return (arg);
		*i = *i + 1;
	}
	return (arg);
}
