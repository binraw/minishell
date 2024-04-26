/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:18 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/26 11:33:53 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

#include "../pipe/pipex.h"


// essai de mettre cmd dans une structure qui a la valeur de la commande
// mais aussi un tableau de tout les in-redirection
// un tableau de tout les out
typedef  struct s_redir   t_redir;
typedef struct data_s
{
    char	*str;
    char    **cmd;
    char	**env;
    int     number_of_cmd;
    int     number_of_pip;
    int     last_pid;
    t_redir *redir;
} t_data;

typedef struct s_redir
{
    int     in;
    int     out;
    char    *value;
    char    **tab_file_in;
    char    **tab_file_out;
	char	*file_in;
    char    *file_out;
}   t_redir;

int	exe_cmd(t_data *data);
char	**init_cmd(char *argv);
int init_env(t_data *data, char **envp);
int free_env(t_data *data);
int command_env(t_data *data);
int command_exit(int c);
// int init_pip(t_data *data, t_redir *redir);
// int	pipex_process_multi(t_data *data, t_redir *redir, int *pip);
// int	child_process_multi(t_data *data, t_redir *redir, int i, int *pip);
// int	second_child_process_multi(t_data *data, t_redir *redir, int i, int *pip);

int init_pip(t_data *data);
int	pipex_process_multi(t_data *data, int **pip, pid_t *tab_pid);
int	child_process_multi(t_data *data,  int i, int *pip);
int	second_child_process_multi(t_data *data, int i, int **pip, int y);

int init_values_parse(t_data *data);
int count_cmd(t_data *data);
int count_pip(t_data *data);
int free_data_values(t_data *data);
int	process_status_pid(t_data *data, pid_t *tab_pid);
int	second_child(t_data *data, int i, int **pip, int y);
int init_values_redir(t_data *data);

#endif