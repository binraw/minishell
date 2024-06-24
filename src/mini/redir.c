/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:26 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/24 12:33:17 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"




int open_all_redir(t_node_cmd *cmd)
{
	int i;
	t_redir *dup;

	dup = cmd->redir;
	i = 0;
	while (dup)
	{
		if (dup->in)	
			open_redir_in(dup);
		else if (dup->out)
 			open_redir_out(dup);
		else if (dup->d_out)
			open_redir_d_out(dup);
		dup = dup->next;
	}
	return (0);
}


int	open_redir_in(t_redir *dup)
{
	int i;
	t_redir *last_in;

	last_in = get_last_in(dup);
	i = 0;
	if (dup != last_in)
	{
		i = open(dup->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
        if (i < 0)
		{
			printf("cat: %s: Permission denied\n", dup->content);
        	return (-1);
		}
		close(i);
	}
	return (0);
}

int open_redir_out(t_redir *dup)
{
	int i;
	t_redir *last_out;

	last_out = get_last_out(dup);
	i = 0;
	if (dup != last_out)
	{
		i =  open(dup->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
	   	if (i < 0)
			return (-1);
		close(i);
	}
	return (0);
}

int	open_redir_d_out(t_redir *dup)
{
	int i;
	t_redir *last_out;

	last_out = get_last_out(dup);
	i = 0;
	if (dup != last_out)
	{
		i = open(dup->content, (O_WRONLY | O_APPEND), 00644);
		if (i < 0)
		{
			printf("cat: %s: Permission denied\n", dup->content);
			return (-1);
		}
		close(i);
	}
	return (0);
}








			

int ft_dup_redir_second_child(t_data *data, t_node_cmd *cmd , int **pip, int y)
{
	int fd_in;
	int fd_out;

	if (open_all_redir(cmd) == -1)
		return (-1);
	fd_in = value_final_in(cmd);
	fd_out = value_final_out(cmd);
    if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)
            && get_last_in(cmd->redir) && !(get_last_out(cmd->redir)))
		redir_in_to_pipe(pip, y, fd_in);
    else if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)
            && get_last_in(cmd->redir) && get_last_out(cmd->redir))
		redir_in_out_to_pipe(pip, y, fd_in, fd_out);
    else if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)
        && !(get_last_in(cmd->redir)) && get_last_out(cmd->redir))
		redir_out_to_pipe(pip, y, fd_out);
	else 
		redir_in_or_out(cmd, pip, y);
   return (0);
}

int	value_final_in(t_node_cmd *cmd)
{
	int fd_in;

	fd_in = 0;
	if (get_last_in(cmd->redir) && cmd->fd_rdoc == 0)
	{
		fd_in = open(get_last_in(cmd->redir)->content , (O_RDONLY), 00644);
		if (fd_in <= 0)
			exit(-1);
	}
	else 
		fd_in = cmd->fd_rdoc;
	return (fd_in);
}

int	value_final_out(t_node_cmd *cmd)
{
	int fd_out;

	fd_out = 0;
	if (get_last_out(cmd->redir))
	{
		if (get_last_out(cmd->redir)->d_out)
			fd_out = open(get_last_out(cmd->redir)->content, (O_WRONLY | O_APPEND), 00644);
		else
			fd_out = open(get_last_out(cmd->redir)->content, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
	}
	return (fd_out);
}

void	redir_in_to_pipe(int **pip, int y, int fd_in)
{
		close(pip[y][1]);
		dup2(fd_in, STDIN_FILENO);
		close(pip[y][0]);
		dup2(pip[y + 1][1], STDOUT_FILENO);
		close(pip[y + 1][1]);
		close(pip[y + 1][0]);
        close(fd_in);
}

void	redir_in_out_to_pipe(int **pip, int y, int fd_in, int fd_out)
{
		close(pip[y][1]);		
		dup2(fd_in, STDIN_FILENO);
		close(pip[y][0]);
		dup2(fd_out, STDOUT_FILENO);
		close(pip[y + 1][1]);
		close(pip[y + 1][0]);
        close(fd_in);
        close(fd_out);
}

void	redir_out_to_pipe(int **pip, int y, int fd_out)
{
		close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		close(pip[y][0]);
		dup2(fd_out, STDOUT_FILENO);
		close(pip[y + 1][1]);
		close(pip[y + 1][0]);
        close(fd_out);
}

void	redir_in_or_out(t_node_cmd *cmd, int **pip, int y)
{
	if (get_last_in(cmd->redir))
		{
			dup2(value_final_in(cmd), STDIN_FILENO);
			close(value_final_in(cmd));
		}
		else 
			dup2(pip[y][0], STDIN_FILENO);
		if (get_last_out(cmd->redir))
		{
			dup2(value_final_out(cmd), STDOUT_FILENO);//javais mis de base fd_in
			close(value_final_out(cmd));
		}
		close(pip[y][0]);
		close(pip[y][1]);
}


















int     ft_redir_child_process(t_node_cmd *cmd, int *pip)
{
	int fd_out;
	int fd_in;

	if (get_last_out(cmd->redir))
	{
		fd_out = value_final_out(cmd);
    	close(pip[0]);
		dup2(fd_out, STDOUT_FILENO);
		close(pip[1]);
    	close(fd_out);
	}
	else if (get_last_in(cmd->redir))
	{
		fd_in = value_final_in(cmd);
    	close(pip[0]);
		dup2(fd_in, STDIN_FILENO);
		dup2(pip[1], STDOUT_FILENO);
		close(pip[1]);
    	close(fd_in);
	}
    return (0);
}


int		ft_redir_one_process(t_node_cmd *cmd)
{
	int fd_out;
	int	fd_in;

	if (open_all_redir(cmd) == -1)
		return (-1);
	fd_in = value_final_in(cmd);
	fd_out = value_final_out(cmd);
	if (!(get_last_in(cmd->redir)) && get_last_out(cmd->redir))
	{
		dup2(fd_out, STDOUT_FILENO);
    	close(fd_out);
	}
	else if (get_last_in(cmd->redir) && !(get_last_out(cmd->redir)))
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
		redir_one_in_out(fd_in, fd_out);
    return (0);
}
	
void	redir_one_in_out(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

