/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:00:16 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/28 14:43:09 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>

void	handle_sigint_after(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
}

// void	setup_readline_sigquit_after(void)
// {
// 	struct sigaction	act;

// 	ft_bzero(&act, sizeof(act));
// 	act.sa_handler = &handle_sigquit;
// 	sigaction(SIGQUIT, &act, NULL);
// }

void	handle_rdocs(int sig)
{
	(void) sig;
	g_interrupted = 1;
	rl_on_new_line();
	ioctl(0, TIOCSTI, "\n");
}

void	setup_readline_rdocs(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_rdocs;
	sigaction(SIGINT, &act, NULL);
	setup_readline_sigquit();
}

void	after_handle_sigquit(int sig)
{
	(void) sig;
}
