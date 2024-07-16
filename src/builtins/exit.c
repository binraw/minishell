// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   exit.c                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/07/15 10:43:53 by rtruvelo          #+#    #+#             //
//   Updated: 2024/07/15 15:33:19 by rtruvelo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../mini/mini.h"

int command_exit(t_node_cmd *cmd)
{
	ft_putstr_fd("exit\n", 1);
	if (!(cmd->content[1]))
		exit(0);
	if ((ft_is_numeric(cmd->content[1]) == 0))
		exit(exit_error_number(cmd->content[1]));
	else if (cmd->content[1] && !cmd->content[2])
		exit(ft_atoi(cmd->content[1]));
	else
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 1);
		return (2);
	}
}


int	ft_is_numeric(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int	exit_error_number(char *arg)
{
	ft_putstr_fd("bash: exit: ",1);
	ft_putstr_fd(arg, 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	return (2);
}
