/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:18 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/16 14:55:05 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

#include "../pipe/pipex.h"

typedef struct data_s
{
    char	*str;
    char    **cmd;
    char	**env;
    int     number_of_cmd;
    int     nummber_of_pip;

} t_data;

int	exe_cmd(t_data *data);
char	**init_cmd(char *argv);
int init_env(t_data *data, char **envp);
int free_env(t_data *data);
int command_env(t_data *data);
int command_exit(int c);
int init_pip(t_data *data);
int	pipex_process_multi(t_data *data, int *pip);
int	child_process_multi(t_data *data, int i, int *pip);
int	second_child_process_multi(t_data *data, int i, int *pip);

#endif