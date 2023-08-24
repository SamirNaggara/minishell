/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:49:28 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/24 23:51:33 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirect_fdin(t_simple_cmd *cmd)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (0);
	close(cmd->fd_in);
	return (1);
}

int	ft_redirect_fdout(t_simple_cmd *cmd)
{
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (0);
	close(cmd->fd_out);
	return (1);
}

void	ft_close_redir_fds(t_data *data)
{
	t_simple_cmd	*browse;

	browse = data->first_cmd;
	while (browse)
	{
		if (browse->fd_in != -1)
			close (browse->fd_in);
		if (browse->fd_out != -1)
			close(browse->fd_out);
		browse = browse->next;
	}
}
