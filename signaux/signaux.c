/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:16:55 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 12:27:20 by snaggara         ###   ########.fr       */
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
void handler_c(int signum)
{
	//fd_printf(STDERR_FILENO, "Le signal %d avec le global state %d\n", signum, g_global_state);
	if (signum == SIGINT)
	{
		if (g_global_state == 1)
			return ;
		if (g_global_state == 0)
		{
			ft_printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay(); 
		}
		else if (g_global_state == 2)
			g_global_state = 3;
	}
}

void handler_slash(int signum)
{
	//fd_printf(STDERR_FILENO, "Le signal %d avec le global state %d\n", signum, g_global_state);
	if (signum == SIGQUIT)
	{
		fd_printf(STDERR_FILENO, "Quit (core dumped)\n");
		exit(1);
	}
}

int	ft_signal(void)
{
	struct sigaction sa;
    sigemptyset(&sa.sa_mask);
	
	
    sa.sa_handler = handler_c;
    sa.sa_flags = 0;


    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction failed");
        return (1);
    }
	return (1);
}

int	ft_signal_slash(void)
{
	struct sigaction sa2;
	
    sigemptyset(&sa2.sa_mask);
	sa2.sa_handler = handler_slash;
    sa2.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa2, NULL) == -1) {
        perror("sigaction failed");
        return (1);
    }
	return (1);
}

int	ft_signal_slash_ignore(void)
{
	struct sigaction sa2;
	
    sigemptyset(&sa2.sa_mask);
	sa2.sa_handler = SIG_IGN;
    sa2.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa2, NULL) == -1) {
        perror("sigaction failed");
        return (1);
    }
	return (1);
}

int	ft_signal_ignore(void)
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction failed");
        exit(EXIT_FAILURE);
    }
	return (1);
}

void	ft_set_terminal_settings(t_data *data)
{
	tcgetattr(STDIN_FILENO, &data->terminal);
	data->terminal.c_lflag |= ICANON;
	data->terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->terminal);
}

// int	ft_signal_slash_restore(void)
// {
// 	struct sigaction sa;
// 	sigemptyset(&sa.sa_mask);

// 	sa.sa_handler = SIG_DFL;
// 	sa.sa_flags = 0;
// 	if (sigaction(SIGQUIT, &sa, NULL) == -1) {
//         perror("sigaction failed");
//         exit(EXIT_FAILURE);
//     }
// 	return (1);
// }

