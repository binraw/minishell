/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:55:55 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/09 15:04:50 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H


typedef struct data_s
{
    char	*str;
    char	**env;
    
} t_data;

int	exe_cmd(t_data *data, char **envp);
char	**init_cmd(char *argv);
int init_env(t_data *data, char **envp);

#endif