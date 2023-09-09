/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:16:55 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/09 11:28:00 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handler(int signum) {
    printf("Signal SIGINT reçu. Mais on continue ! %d\n", signum);
}

int	ft_signal(void)
{
	struct sigaction sa;
    sigemptyset(&sa.sa_mask);
	
    sa.sa_handler = handler;
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return (1);
    }
	return (1);
}