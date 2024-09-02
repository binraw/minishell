/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:18:58 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/25 10:48:46 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**create_cmd(char **argv, int i)
{
	char	**cmd;
	int		y;

	y = 0;
	if (argv[i][y] == '\0')
		return (NULL);
	while (argv[i][y] == ' ')
	{
		if (argv[i][y + 1] == '\0')
			return (NULL);
		y++;
	}
	cmd = ft_split(argv[i], ' ');
	return (cmd);
}
