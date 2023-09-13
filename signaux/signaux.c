/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:16:55 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/13 15:27:02 by snaggara         ###   ########.fr       */
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
void handler_c(int signum) {
	if (global_state == 1)
		return ;
	if (signum == SIGINT)
	{
		if (global_state == 0)
		{
			ft_printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay(); 
		}
		else if (global_state == 2)
			global_state = 3;
	}
}

int	ft_signal(void)
{
	struct sigaction sa;
    sigemptyset(&sa.sa_mask);
	
    sa.sa_handler = handler_c;
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return (1);
    }
	return (1);
}

