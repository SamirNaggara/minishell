/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:16:55 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/26 19:56:18 by snaggara         ###   ########.fr       */
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

/*
	Gerer le signal du controle plus c
*/
int	ft_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler_c;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction failed");
		return (1);
	}
	return (1);
}

/*
	Pour les moments ou on a besoin d'ignorer le signal
*/
int	ft_signal_ignore(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction failed");
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	ft_init_signal_loop(void)
{
	struct sigaction initSa;
	struct sigaction ignoreSa;

    sigemptyset(&initSa.sa_mask);
    sigemptyset(&ignoreSa.sa_mask);

    initSa.sa_handler = handler_c;
    initSa.sa_flags = 0;
	ignoreSa.sa_handler = SIG_IGN;
    ignoreSa.sa_flags = 0;

    sigaction(SIGINT, &initSa, NULL);
    sigaction(SIGQUIT, &ignoreSa, NULL);
}

void	ft_signal_reinit(void)
{
        struct sigaction sa_default;

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

void	ft_here_doc()
{
	struct sigaction hereDocSa;

    sigemptyset(&hereDocSa.sa_mask);
    hereDocSa.sa_handler = handler_here_doc;
    hereDocSa.sa_flags = 0;
    sigaction(SIGINT, &hereDocSa, NULL);
}

void	ft_signal_slash_reinit(void)
{
	struct sigaction slash_default;

	slash_default.sa_handler = SIG_DFL;
	sigemptyset(&slash_default.sa_mask);
	slash_default.sa_flags = 0;
	sigaction(SIGQUIT, &slash_default, NULL);
}
