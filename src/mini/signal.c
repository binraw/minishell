/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:57:44 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/06/05 15:48:17 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "mini.h"
#include <stdlib.h>
void setup_readline_sigquit_after(void);
void	handle_sigint_after(int sig);

volatile sig_atomic_t interrupted = 0;
// CHANGEZ TOUT LE NOMS DES VARIABLES
void	handle_sigint(int sig)
{
	(void) sig;

	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
}


void	handle_sigquit(int sig)
{
	(void) sig;

}

void setup_readline_signals(void)
{
	// Declare the sigaction structure
	struct sigaction	act;

	bzero(&act, sizeof(act));
	act.sa_handler = &handle_sigint;
	sigaction(SIGINT, &act, NULL);
	setup_readline_sigquit();
}

void setup_readline_sigquit(void)
{
	// Declare the sigaction structure
	struct sigaction	act;

	bzero(&act, sizeof(act));

	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	after_readline_signals(void)
{
/*	rl_catch_signals = 0;*/
	struct sigaction	act;

	bzero(&act, sizeof(act));
	act.sa_handler = &handle_sigint_after;
	sigaction(SIGINT, &act, NULL);
	setup_readline_sigquit_after();
}

void	after_handle_sigquit(int sig)
{
	(void) sig;

	rl_replace_line("new line bg\n", 0);
}

void	handle_sigint_after(int sig)
{
	(void) sig;

	printf("\n");
}




void setup_readline_sigquit_after(void)
{
	// Declare the sigaction structure
	struct sigaction	act;

	bzero(&act, sizeof(act));

	act.sa_handler = &handle_sigquit;
	sigaction(SIGQUIT, &act, NULL);
}

void	handle_rdocs(int sig)
{
	(void) sig;
	interrupted = 1;
	rl_on_new_line();  
	ioctl(0,TIOCSTI, "\n");


}

void setup_readline_rdocs(void)
{
	// Declare the sigaction structure
	struct sigaction	act;

	bzero(&act, sizeof(act));
	act.sa_handler = &handle_rdocs;
	sigaction(SIGINT, &act, NULL);
	setup_readline_sigquit();
}

