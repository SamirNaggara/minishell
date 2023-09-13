/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:43:39 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/13 09:43:43 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_inf_inf_operator(t_simple_cmd *cmd, t_lexer *redirection)
{
	if (redirection->operator != INFINF)
		return (1);
	if (!ft_handle_here_doc(cmd, redirection))
		return (0);
	redirection->operator = INF;
	return (1);
}
