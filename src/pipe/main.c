/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:18:58 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/09 11:12:59 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	int	fd[2];
// 	int	control;

// 	control = 0;
// 	if (argc == 5)
// 	{
// 		pipe(fd);
// 		control = pipex_process(argv, envp, fd);
// 		close(fd[0]);
// 		close(fd[1]);
// 	}
// 	return (control);
// }

int	pipex_process(char **argv, char **envp, int *fd)
{
	pid_t	first_child;
	pid_t	second_child;
	int		status;

	status = 0;
	first_child = fork();
	if (first_child == -1)
		return (-1);
	if (first_child == 0)
		child_process(argv, envp, fd);
	second_child = fork();
	if (second_child == -1)
		return (-1);
	if (second_child == 0)
		second_child_process(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(first_child, &status, 0);
	waitpid(second_child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	child_process(char **argv, char **envp, int *fd)
{
	int		filein;
	char	**command;
	char	*path_command;

	path_command = NULL;
	command = create_cmd(argv, 2);
	if (command)
		path_command = create_path(command[0], envp);
	if (!path_command)
		return (error_path(command, 2, argv), -2);
	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		return (error_file(command, path_command, 1, argv), -1);
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(filein);
	close(fd[1]);
	close(fd[0]);
	execve(path_command, command, envp);
	perror("execve");
	exit(127);
	return (0);
}

char	**create_cmd(char **argv, int i)
{
	char	**cmd;
	int		y;

	y = 0;
	if (argv[i][y] == '\0')
		return (NULL);
	while (argv[i][y] == ' ')
	{
		if (argv[i][y + 1] == '\0')
			return (NULL);
		y++;
	}
	cmd = ft_split(argv[i], ' ');
	return (cmd);
}

int	second_child_process(char **argv, char **envp, int *fd)
{
	int		fileout;
	char	**command;
	char	*path_command;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	path_command = NULL;
	command = create_cmd(argv, 3);
	if (command)
		path_command = create_path(command[0], envp);
	if (!path_command)
		error_path(command, 3, argv);
	if (fileout == -1)
		return (open_error_file(command, path_command, 4, argv), -1);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	close(fd[0]);
	close(fd[1]);
	execve(path_command, command, envp);
	perror("execve");
	exit(127);
	return (0);
}
