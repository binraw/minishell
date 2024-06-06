/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:18 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/05 14:21:50 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H



#include <stdio.h>
#include "../pipe/pipex.h"
#include "../../lib/libft/libft.h"
#include <signal.h>

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
	char				**content; // valeur de la commande 
	struct node_cmd_s	*next;
	t_redir				*redir; // ici possible changement de ta part pour gerer les redirection si tu veux faire des liste chainees a la place jsp 
    t_rdocs				*rdocs; // ici possible changement de ta part pour gerer les rdocs 
   	int					fd_rdoc; 
}   t_node_cmd;

typedef struct s_redir
{
	bool	in;
	bool	out;
	bool	d_out;
	bool	rdocs;
	char	*content;
	t_redir	*next;
}  	t_redir;

typedef struct s_rdocs
{
    char    *str_rdocs;
    char    *limit;
    bool    go;
	t_rdocs	*next;
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
/*char	**init_cmd(char *argv);*/
/*char	**init_cmd(t_data *data ,char *argv);*/
int init_env(t_data *data);
int free_env(t_data *data);
int command_env(t_data *data);
int command_exit(int c);
int init_pip(t_data *data);
int init_values_parse(t_data *data);
int count_cmd(t_data *data);
int count_pip(t_data *data);
int	pipex_process_multi(t_data *data, int **pip, pid_t *tab_pid);
int	pipex_process_multi(t_data *data, int **pip, pid_t *tab_pid);
int	child_process_multi(t_data *data, t_node_cmd *cmd, int *pip);
int	second_child_process_multi(t_data *data, t_node_cmd *cmd, int **pip, int y);
int free_data_values(t_data *data);
int	process_status_pid(t_data *data, pid_t *tab_pid, int *status);
int init_values_redir(t_data *data);
int	second_child(t_data *data, int **pip, int y, t_node_cmd *cmd);
int ft_dup_redir_second_child(t_data *data, t_node_cmd *cmd, int **pip, int y);
int     ft_redir_child_process(t_node_cmd *cmd, int *pip);
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
void    ft_lstclear_cmd(t_node_cmd **lst);
int	ft_lstadd_back_cmd(t_node_cmd *lst, t_node_cmd *new_node);
t_node_cmd	*ft_lstlast_cmd(t_node_cmd *lst);
t_node_cmd	*ft_lstnew_cmd(int i);
int init_node_cmd(t_data *data, char **tab);
/*char	**init_cmd(t_data *data ,char *argv);*/
t_node_cmd	*cmd_get_content(char *str, size_t index);
int		ft_redir_one_process(t_node_cmd *cmd);
int	open_all_rdocs(t_node_cmd *cmd);
int init_rdocs(t_rdocs *rdocs);
int command_rdocs(t_data *data);
void	handle_sigint(int sig);
void setup_readline_signals(void);
void	handle_sigquit(int sig);
int analyze_process_statuses(t_data *data,pid_t *tab_pid, int *status);
void	after_readline_signals(void);
void	after_handle_sigquit(int sig);
void setup_readline_sigquit(void);







void	init_cmd(t_data *data ,char *argv);
t_redir	*redir_lst_new(int type, char *tok);
void	ft_lstclear_redir(t_redir **lst);
t_redir	*get_last_in(t_redir *redir);
t_redir	*get_last_out(t_redir *redir);
t_redir	*get_last_rdocs(t_redir *redir);
t_redir	*get_last_d_out(t_redir *redir);
int		manage_quotes(char c, int quote);
size_t	ft_count_str(char *str, char sep);
char	*tok_stop_redir(char *str, size_t i);
char	*tok_redir(char *str, size_t *i);
char	*ft_strtok(char	*str, char *sep, bool redir);
void	fill_redirs(char *tok, t_redir **redir, t_rdocs **rdocs);
t_node_cmd	*cmd_get_content(char *str, size_t index);
char	*trim_redir(char *tok, int i);
char	*create_tok(char *sep, char *ptr, bool redir, size_t *i);
t_redir	*init_redirs(char *tok, t_rdocs **rdocs);
void	fill_cmd_content(t_data *data, char **pips);
t_redir	*fill_rdocs(char *tok, t_rdocs **rdocs);
t_rdocs	*ft_lstnew_rdocs(char *str);
void	ft_lstclear_rdocs(t_rdocs **lst);
#endif
