/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:55:55 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/09 14:07:37 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H


typedef struct data_s
{
    char *str;
    
} t_data;

int	exe_cmd(t_data *data, char **envp);
char	**init_cmd(char *argv);

#endif