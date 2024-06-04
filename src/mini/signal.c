/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:57:44 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/04 14:15:51 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "mini.h"
#include <stdlib.h>


void	handle_sigint(int sig)
{
	(void) sig;

	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
};


void	handle_sigquit(int sig)
{
	(void) sig;

	rl_replace_line("", 0);
}

void setup_readline_signals(void)
{
    rl_catch_signals = 0; // Désactiver la gestion interne des signaux par readline
    signal(SIGINT, handle_sigint); // Associer le signal SIGINT à notre gestionnaire
	signal(SIGQUIT, handle_sigquit);
}
