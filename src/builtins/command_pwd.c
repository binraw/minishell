// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   command_pwd.c                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/21 16:34:47 by rtruvelo          #+#    #+#             //
//   Updated: 2024/08/21 16:38:47 by rtruvelo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../mini/mini.h"

int	command_pwd(t_data *data, int fd)
{
	char	*pos;
	long	size;

	size = 20;
	while (1)
	{
		pos = malloc((size_t)size * sizeof(char *));
		if (!pos)
			empty_pos(data);
		if (getcwd(pos, (size_t)size) != NULL)
		{
			ft_putstr_fd(pos, fd);
			ft_putchar_fd('\n', fd);
			free(pos);
			break ;
		}
		else
		{
			free(pos);
			size += size;
		}
	}
	return (1);
}
