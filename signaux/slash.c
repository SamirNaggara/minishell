/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:16:21 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/26 15:53:58 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Pour le signal contrl + \ quand on est dans un here doc
*/
void	handler_slash(int signum)
{
	if (signum == SIGQUIT)
		fd_printf(STDERR_FILENO, "Quit (core dumped)\n");
}

/*
	Le signal du slash quand on est dans un here doc
*/
int	ft_signal_slash(void)
{
	struct sigaction	sa2;

	sigemptyset(&sa2.sa_mask);
	sa2.sa_handler = handler_slash;
	sa2.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa2, NULL) == -1)
	{
		perror("sigaction failed");
		return (1);
	}
	return (1);
}

/*
	Ignorer le slash en general
*/
int	ft_signal_slash_ignore(void)
{
	struct sigaction	sa2;

	sigemptyset(&sa2.sa_mask);
	sa2.sa_handler = SIG_IGN;
	sa2.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa2, NULL) == -1)
	{
		perror("sigaction failed");
		return (1);
	}
	return (1);
}
