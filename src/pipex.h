/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:34:28 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/03/21 13:23:56 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h> 
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../lib/libft/libft.h"

int		pipex_process(char **argv, char **envp, int *fd);
int		child_process(char **argv, char **envp, int *fd);
int		second_child_process(char **argv, char **envp, int *fd);
char	**create_cmd(char **argv, int i);
char	**get_env(char **envp);
int		main(int argc, char **argv, char **envp);
char	*create_path(char *cmd, char **envp);
void	error_pipe(int error, int i, char **argv);
void	ft_free_tab(char **tab);
void	error_file(char **command, char *path_command, int i, char **argv);
void	error_path(char **command, int i, char **argv);
void	open_error_file(char **command, char *path_command, int i, char **argv);

#endif