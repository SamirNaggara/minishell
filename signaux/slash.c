/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:16:21 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/26 20:10:03 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signal_slash_reinit(void)
{
	struct sigaction	slash_default;

	slash_default.sa_handler = SIG_DFL;
	sigemptyset(&slash_default.sa_mask);
	slash_default.sa_flags = 0;
	sigaction(SIGQUIT, &slash_default, NULL);
}
