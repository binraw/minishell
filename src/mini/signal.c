/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:57:44 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/07/30 13:45:41 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "mini.h"
#include <stdlib.h>
void setup_readline_sigquit_after(void);
void	handle_sigint_after(int sig);

volatile sig_atomic_t interrupted = 0;

void	handle_sigint(int sig)
{
	(void) sig;

	 rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}


void	handle_sigquit(int sig)
{
	(void) sig;
}

void setup_readline_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_sigint;
	sigaction(SIGINT, &act, NULL);
	setup_readline_sigquit();
}

void setup_readline_sigquit(void)
{
	struct sigaction	act;

	bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	after_readline_signals(t_data *data)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_sigint_after;
	if (rl_line_buffer[0] == '\0')
	{
		ft_lstclear_data(data);
		exit(0);
	}
	sigaction(SIGINT, &act, NULL);
	setup_readline_sigquit_after();
}


void	after_handle_sigquit(int sig)
{
	(void) sig;

}

void	handle_sigint_after(int sig)
{
	(void) sig;

	write(1, "\n", 1);
	rl_on_new_line();
}




void setup_readline_sigquit_after(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
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
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_rdocs;
	sigaction(SIGINT, &act, NULL);
	setup_readline_sigquit();
}

