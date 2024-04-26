/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/26 14:14:08 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../pipe/pipex.h"
#include "mini.h"

int main(int argc, char **argv, char **envp) 
{
	t_data vars;
	(void)argv;
	(void)argc;
	
	init_env(&vars, envp);
    while (1)
    {
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

int init_env(t_data *data, char **envp)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	while (envp[y])
		y++;
	data->env = malloc(sizeof(char**) * (y + 1) );
	if (!data->env)
		return (-1);
	while (i < y )
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			return (-1);
		i++;
	}
	data->env[i] = NULL;
	return (0);
}

int free_env(t_data *data)
{
	size_t i;

	i = 0;
	if (data->env)
	{
	while (data->env[i])
	{
		free(data->env[i++]);
	}
	free(data->env);
	data->env = NULL;
	}
	return (0);
}

