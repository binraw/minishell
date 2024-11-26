/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/26 10:04:22 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	(void)argc;
	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	ft_bzero(data, sizeof(t_data));
	init_node_env(data, envp);
	data->last_pid = 0;
	data->free_pid = true;
	loop_main(data);
	ft_lstclear_data(data);
	return (0);
}

void	loop_main(t_data *data)
{
	while (1)
	{
		init_env(data);
		setup_readline_signals(data);
		data->str = readline("Minishell: ");
		if (!data->str)
			break ;
		add_history(data->str);
		if (init_cmd(data, data->str))
			init_pip(data);
		data->cmd = ft_lstclear_cmd(data->cmd);
		if (!data->free_pid)
			free_exec_part(data);
		free(data->str);
	}
}
