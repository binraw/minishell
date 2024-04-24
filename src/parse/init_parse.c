/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:02:52 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/24 11:12:27 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int init_values_parse(t_data *data)
{
    int i;

    i = 0;
    data->last_pid = 0;
    data->number_of_pip = count_pip(data);
    data->number_of_cmd = count_cmd(data);
    data->cmd = malloc(data->number_of_cmd * sizeof(char*));
    data->cmd = init_cmd(data->str);
    
    return (0);
}
int count_pip(t_data *data)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(data->str[i])
    {
        if (data->str[i] == ' ') // je compte avec des espace pour test
            count++;
        i++;
    }
    return (count);
}

int count_cmd(t_data *data)
{
    int i;
    int count;
    
    i = 0;
    count = 1;
    if (!data->str)
        return (0);
    while (data->str[i])
    {
        if (data->str[i] != ' ')
        {
            i++;
        }
        if (data->str[i] == ' ')
        {
            count++;
            i++;
        }
    }
    if (data->str[i] == '\0' && count == 0)
        count++;
    return (count);
}


int free_data_values(t_data *data)
{
    int i;

    i = 0;
    while (data->number_of_cmd > 0)
    {
        free(data->cmd[data->number_of_cmd]);
        data->number_of_cmd--;
    }
    free(data->cmd);
    free(data->str);
    return (0);
}
// char    *cut_cmd(char *str)
// {
    
// }