// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   utils_builtins.c                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/22 12:45:14 by rtruvelo          #+#    #+#             //
//   Updated: 2024/08/22 12:46:21 by rtruvelo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "mini.h"

void	env_process_child(t_data *data, int pip)
{
	command_env(data, pip);
	ft_lstclear_data(data);
	exit(0);
}

void	pwd_process_child(t_data *data, int pip)
{
	command_pwd(data, pip);
	ft_lstclear_data(data);
	exit(0);
}

int	print_error_cd(t_node_cmd *cmd)
{
	ft_putstr_fd("bash :", 2);
	ft_putstr_fd(cmd->content[1], 2);
	ft_putstr_fd(" :No such file or directory\n", 2);
	return (0);
}
