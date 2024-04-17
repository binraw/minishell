/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:02:52 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/17 15:39:08 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

int init_values_parse(t_data *data)
{
    data->number_of_pip = count_pip(data);
    data->number_of_cmd = count_cmd(data);
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
        if (data->str[i] == '|')
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
    count = 0;
    if (!data->str)
        return (0);
    while (data->str[i])
    {
        if (data->str[i] != ' ')
        {
            i++;
        }
        if (data->str[i] == ' ' && data->str[i - 1] != ' ' && data->str[i - 1] != '|')
        {
            count++;
            i++;
        }
        i++;
    }
    if (data->str[i] == '\0' && count == 0)
        count++;
    return (count);
}
// char    *cut_cmd(char *str)
// {
    
// }