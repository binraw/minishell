/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:18 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/17 15:40:16 by rtruvelo         ###   ########.fr       */
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
    int     number_of_pip;

} t_data;

typedef struct s_redir
{
    int     in;
    int     out;
    char    **tab_file;
	char	*file_in;
    char    *file_out;
}   t_redir;

int	exe_cmd(t_data *data);
char	**init_cmd(char *argv);
int init_env(t_data *data, char **envp);
int free_env(t_data *data);
int command_env(t_data *data);
int command_exit(int c);
int init_pip(t_data *data, t_redir *redir);
int	pipex_process_multi(t_data *data, t_redir *redir, int *pip);
int	child_process_multi(t_data *data, t_redir *redir, int i, int *pip);
int	second_child_process_multi(t_data *data, t_redir *redir, int i, int *pip);
int init_redir(t_redir *redir);
int ft_redir_in(t_redir *redir);
int ft_redir_out(t_redir *redir);
int init_values_parse(t_data *data);
int count_cmd(t_data *data);
int count_pip(t_data *data);


#endif