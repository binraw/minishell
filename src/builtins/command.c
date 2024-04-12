/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:49:40 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/12 11:15:07 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int command_env(t_data *data)
{
    size_t i;

    i = 0;
    while (data->env[i])
    {
        printf("%s\n", data->env[i]);
        i++;
    }
    return (0);
}

int command_exit(int c)
{
    exit((unsigned char)c);
}

// int command_pwd(void)  // changer quand on pourra ajouter des arguments
// {
//     char pwd[1024];

//     getcwd(pwd, sizeof(pwd));
//     printf("%s\n", pwd);
//     free(pwd);
//     return (0);
// }

// int command_unset(t_data *data, char *var)
// {
//     char *name_of_var;
//     size_t i;

//     i = 0;
//     name_of_var = malloc((ft_strlen(var) + 1) * sizeof(char*));
    
//     while (i < (ft_strlen(var) - 1))
//     {
//         name_of_var[i] = var[i];
//         i++;
//     }
//     name_of_var[i++] = '=';
//     name_of_var[i] = '\0';

// // la jai rajouter le = apres ma variable mais je suis pas sur de devoir le faire pour supprimer ou juste verifier si y a bien un egal apres 
    

// }