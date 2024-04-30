/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:18 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/30 11:26:22 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H



#include <stdio.h>
#include "../pipe/pipex.h"


// essai de mettre cmd dans une structure qui a la valeur de la commande
// mais aussi un tableau de tout les in-redirection
// un tableau de tout les out
#include <stdbool.h>

typedef  struct s_redir   t_redir;
typedef struct s_rdocs  t_rdocs;
typedef struct node_env_s   t_node_env;


typedef struct data_s
{
    char	*str;
    char    **cmd;
    char	**env;
    int     number_of_cmd;
    int     number_of_pip;
    int     last_pid;
    t_redir *redir;
    t_rdocs *rdocs;
    t_node_env  *env_node;
    
} t_data;

typedef struct s_redir
{
    int     in;
    int     out;
    char    *value;
    char    **tab_file_in;
    char    **tab_file_out;
}   t_redir;

typedef struct s_rdocs
{
    char    *str_rdocs;
    char    *limit;
    bool    go;
}   t_rdocs;

typedef struct node_env_s
{
    char                *value;
    struct node_env_s	*next;
    

}   t_node_env;

int	exe_cmd(t_data *data);
char	**init_cmd(char *argv);
int init_env(t_data *data, char **envp);
int free_env(t_data *data);
int command_env(t_data *data);
int command_exit(int c);
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
int ft_dup_redir_second_child(t_data *data , int **pip, int y , int i);
int     ft_redir_child_process(t_data *data, int *pip, int i);
int first_child(int *pip);
int	ft_lstadd_back(t_node_env **lst, t_node_env *new);
t_node_env	*ft_lstlast(t_node_env *lst);
t_node_env	*ft_lstnew(char *value);
void	print_liste(t_node_env *liste);
int init_node_env(t_data *data);
int free_env(t_data *data);
int init_env(t_data *data, char **envp);

#endif