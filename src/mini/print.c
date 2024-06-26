/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/14 15:44:00 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../pipe/pipex.h"
#include "mini.h"
#include <stdlib.h>

int main(int argc, char **argv, char **envp) 
{
	t_data vars;
	(void)argv;
	(void)argc;
	int i;

	i = 0;
	init_node_env(&vars, envp);
/* 	print_liste(vars.env_node); */

	// while (i < (ft_lstsize(vars.env_node) - 1))
	// {
	// 	screen_export(&vars, 1);
	// 	i++;
	// }
	// print_liste(vars.env_node);
	// unset_command(&vars, "LANG");
	// printf("DESTRUCTION D'UN NOEUD \n\n\n");
	// print_liste(vars.env_node);
	while (1)
	{
		init_env(&vars);
        vars.str = readline("Minishell: ");
        if (vars.str == NULL)
        {
            printf("Error input.\n");
            return (1);
        }
    
		if (ft_strncmp(vars.str, "exit", ft_strlen(vars.str)) == 0)
    	{
            free(vars.str);
			command_exit(0);
			// command_exit(ft_atoi(argv[1])); la commande finale va ressembler a ca a voir comment on recup les 2 arguments
    	}
		if (ft_strncmp(vars.str, "env", ft_strlen(vars.str)) == 0)
		{
			command_env(&vars);
			exit (0);
		}
		init_values_parse(&vars);
		init_pip(&vars);
		free_data_values(&vars);


    } 

    return (0);
}

int	exe_cmd(t_data *data)
{
	char	*path_command;

	if (!data->str)
		return (0);
	data->cmd = init_cmd(data->str);
	path_command = create_path(data->str, data->env);
	if (!path_command)
	{
		// faire un truc pour quand c'est un fichier
		return (printf("error command\n"), -1);
	}
	execve(path_command, data->cmd, data->env);
	perror("execve");
	return (1);
}


char	**init_cmd(char *argv)
{
	char	**cmd;
	int		y;

	y = 0;
	if (argv[y] == '\0')
		return (NULL);
	while (argv[y] == ' ')
	{
		if (argv[y + 1] == '\0')
			return (NULL);
		y++;
	}
	cmd = ft_split(argv, ' ');
	return (cmd);
}



