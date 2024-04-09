/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:12 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/04/09 11:45:09 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipe/pipex.h"

int main() {
    char *input;

    while (1)
    {
        input = readline("Minishell: ");
        if (input == NULL)
        {
            printf("Error input.\n");
            return (1);
        }
    
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0) // remplace par le signal j'imagine
    	{
            printf("Vous avez entré: %s\n", input);
            free(input);
            exit (0); 
    	}
		printf("Vous avez entré: %s\n", input);
    }
	// if (input)
    // 	free(input);

    return (0);
}