/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/09 15:11:04 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipe/pipex.h"
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
    
		if (ft_strncmp(vars.str, "exit", ft_strlen(vars.str)) == 0) // ajouter le signal "CTRL D" j'imagine
    	{
            free(vars.str);
            exit (0);
    	}
		exe_cmd(&vars, envp);
    }

    return (0);
}


int	exe_cmd(t_data *data, char **envp)
{
	char	*path_command;
	char	**command;
	
	command = init_cmd(data->str);
	path_command = create_path(data->str, envp);
	if (!path_command)
		return (printf("error command\n"), -1);
	execve(path_command, command, envp);
	perror("execve");
	return (0);
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
	data->env = ft_split(envp, '\n');
	printf("%s", data->env[0]);
}