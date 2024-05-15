/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:18 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/15 14:02:18 by rtruvelo         ###   ########.fr       */
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

typedef struct node_cmd_s t_node_cmd;

typedef struct data_s
{
    char        *str;
	t_node_cmd	*cmd;
    //char        **cmd;
    char        *path;
    char        **env;
    int         number_of_cmd;
    int         number_of_pip;
    int         last_pid;
    bool	arg; // jmets ca pour verifier si un arg est present pour echo mais a voir si on peut faire autrement
    t_node_env  *env_node;
    
}   t_data;

typedef struct node_cmd_s
{
	int					index; // index de la commande  
	char				*content; // valeur de la commande 
	struct node_cmd_s	*next;
	t_redir				*redir; // ici possible changement de ta part pour gerer les redirection si tu veux faire des liste chainees a la place jsp 
    t_rdocs				*rdocs; // ici possible changement de ta part pour gerer les rdocs 
    
}   t_node_cmd;

typedef struct node_cmd_s
{
	char	*content;
	

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
    char                *content;
    char                *name;
    char                *value;
    bool		print;
    struct node_env_s	*next;
    

}   t_node_env;

int	exe_cmd(t_data *data);
char	**init_cmd(char *argv);
int init_env(t_data *data);
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
int	ft_lstadd_back(t_node_env *lst, t_node_env *new_node);
t_node_env	*ft_lstlast(t_node_env *lst);
t_node_env	*ft_lstnew(char *content);
void	print_liste(t_node_env *liste);
int init_node_env(t_data *data, char **envp);
int free_env(t_data *data);
t_node_env	*ft_lstduplicate(const t_node_env *original);
void	ft_lstclear(t_node_env **lst, void (*del)(void *));
t_node_env	*ft_lstnew_basic(char *content);

void modifyValue(t_node_env *head, const char *name, const char *newValue);
char	*value_pwd(t_node_env *head);

void modifyValue(t_node_env *head, const char *name, const char *newValue);
int cd_to_home(t_data *data);
void	screen_export(t_data *data, int fd);
int remove_node(t_node_env *current_node, t_node_env *second_node, t_node_env *third_node);
void	change_old_pwd(t_data *data);
char	*value_old_pwd(t_node_env *head);
int	ft_lstsize(t_node_env *head);
int		control_export_value(char *value_content);
int		control_export_name(t_data *data, char *value_content);
int	unset_command(t_data *data, char *value);
#endif
