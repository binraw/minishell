/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:57:44 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/08/28 16:36:30 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>

void	setup_readline_sigquit_after(void);
void	handle_sigint_after(int sig);

volatile sig_atomic_t	g_interrupted = 0;

void	handle_sigint(int sig)
{
	t_data	*data;

	(void)sig;
	data = give_data(NULL);
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
	data->last_pid = 130;
}

void	handle_sigquit(int sig)
{
	(void) sig;
}

void	setup_readline_signals(t_data *data)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_sigint;
	sigaction(SIGINT, &act, NULL);
	setup_readline_sigquit();
	give_data(data);
}

t_data	*give_data(t_data *data)
{
	static t_data	*new;

	if (data)
		new = data;
	else
		return (new);
	return (NULL);
}

void	setup_readline_sigquit(void)
{
	struct sigaction	act;

	bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
