/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:55:55 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/11 11:23:58 by rtruvelo         ###   ########.fr       */
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
    
} t_data;

int	exe_cmd(t_data *data);
char	**init_cmd(char *argv);
int init_env(t_data *data, char **envp);
int free_env(t_data *data);
int command_env(t_data *data);
int command_exit(int c);

#endif