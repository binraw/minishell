/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:38:15 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/24 12:21:02 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	second_child(t_data *data, int **pip, int y, t_node_cmd *cmd)
{
	if (2 != data->number_of_cmd && cmd->index != (data->number_of_cmd -1)) // le 2 cest pour eviter quand i y a eulemnt deux commqnde de rentrer dedans
	{

		close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		close(pip[y][0]);
		dup2(pip[y + 1][1], STDOUT_FILENO);
		close(pip[y + 1][1]);
		close(pip[y + 1][0]);
	}
	else
	{

		close(pip[y][1]);
		dup2(pip[y][0], STDIN_FILENO);
		close(pip[y][0]);
	}
	return (0);
}

int first_child(int *pip)
{

	 close(pip[0]); // les changement de redirect sont fait ici avec une condition sur les dup
	dup2(pip[1], STDOUT_FILENO); // et du coup le dup peut etre fait sur redirect ou pip
	// printf(" bonjour je suis ici :%d\n", pip[1]);
	 close(pip[1]);
	return (0);
}
