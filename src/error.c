/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:39:42 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/03/21 14:12:22 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_pipe(int error, int i, char **argv)
{
	if (error == 1)
		write(2, "Error creating pipe\n", 20);
	else if (error == 2)
	{
		ft_putstr_fd(argv[i], 2);
		write(2, " : permission denied\n", 22);
	}
	else if (error == 3)
	{
		ft_putstr_fd(argv[i], 2);
		write(2, " : command not found\n", 22);
	}
	else
		return ;
}

void	error_file(char **command, char *path_command, int i, char **argv)
{
	if (command)
		ft_free_tab(command);
	free(path_command);
	error_pipe(2, i, argv);
	exit(1);
}

void	open_error_file(char **command, char *path_command, int i, char **argv)
{
	if (command && command[0][1] != 'b')
		ft_free_tab(command);
	else
		free(command);
	free(path_command);
	error_pipe(2, i, argv);
	exit(1);
}

void	error_path(char **command, int i, char **argv)
{
	if (command)
		free(command);
	error_pipe(3, i, argv);
	exit(127);
}
