/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:16:55 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/26 20:11:25 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Etat 0 : Minishell est en attente d'une commande
	Etat 1 : Execution en cours
	Etat 2 : Here doc en cours
	Etat 3 : Le here doc est stoppe
	Etat 4 : Il faut arrete tout les processus enfant
*/
void	handler_c(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global_state = 130;
	}
}

void	ft_init_signal_loop(void)
{
	struct sigaction	init_sa;
	struct sigaction	ignore_sa;

	sigemptyset(&init_sa.sa_mask);
	sigemptyset(&ignore_sa.sa_mask);
	init_sa.sa_handler = handler_c;
	init_sa.sa_flags = 0;
	ignore_sa.sa_handler = SIG_IGN;
	ignore_sa.sa_flags = 0;
	sigaction(SIGINT, &init_sa, NULL);
	sigaction(SIGQUIT, &ignore_sa, NULL);
}

void	ft_signal_reinit(void)
{
	struct sigaction	sa_default;

	sa_default.sa_handler = SIG_IGN;
	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sigaction(SIGINT, &sa_default, NULL);
}

void	handler_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		fd_printf(STDERR_FILENO, "\n");
		close(0);
	}
}

void	ft_here_doc(void)
{
	struct sigaction	here_doc_ds;

	sigemptyset(&here_doc_ds.sa_mask);
	here_doc_ds.sa_handler = handler_here_doc;
	here_doc_ds.sa_flags = 0;
	sigaction(SIGINT, &here_doc_ds, NULL);
}
