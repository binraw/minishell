/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/01 11:05:02 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		result;

	(void)argv;
	(void)argc;
	result = 0;
	data = malloc(sizeof(t_data));
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
	char	*line;

	while (1)
	{
		init_env(data);
		setup_readline_signals(data);
		if (isatty(fileno(stdin)))
			data->str = readline("Minishell: ");
		else
		{
			line = get_next_line(fileno(stdin));
			data->str = ft_strtrim(line, "\n");
			free(line);
		}
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
