/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:47:11 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/24 23:48:13 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	SI c'est la derniere commande
		On prends le fd_in du pipe
		Le stdout est redirigé vers le fdout (stdout ou redir)
*/
int	ft_last_child(t_data *data, t_simple_cmd *cmd, int i)
{
	if (cmd->fd_in != -1)
	{
		if (!ft_redirect_fdin(cmd))
			return (0);
	}
	else
	{
		if (dup2(data->pipe[(i - 1) % 2][0], STDIN_FILENO) == -1)
			return (0);
	}
	if (cmd->fd_out != -1)
	{
		if (!ft_redirect_fdout(cmd))
			return (0);
	}
	ft_close_pipe(data->pipe[(i - 1) % 2]);
	return (1);
}

/*
	Si c'est un enfant du milieu
	Le fd in vient du pipe précédent
	Le fd out vient du pipe présent
*/
int	ft_middle_child(t_data *data, t_simple_cmd *cmd, int i)
{
	if (cmd->fd_in != -1)
	{
		if (!ft_redirect_fdin(cmd))
			return (0);
	}
	else
	{
		if (dup2(data->pipe[(i - 1) % 2][0], STDIN_FILENO) == -1)
			return (0);
	}
	if (cmd->fd_out != -1)
	{
		if (!ft_redirect_fdout(cmd))
			return (0);
	}
	else
	{
		if (dup2(data->pipe[i % 2][1], STDOUT_FILENO) == -1)
			return (0);
	}
	ft_close_pipe(data->pipe[i % 2]);
	ft_close_pipe(data->pipe[(i - 1) % 2]);
	return (1);
}

/*
	Si c'est le premier enfant
		Le stdin vient de fdin (stdin ou enfant)
		Le stdout ecrit dans le pipe qu'on vient de creer
*/
int	ft_first_child(t_data *data, t_simple_cmd *cmd, int i)
{
	if (cmd->fd_in != -1)
	{
		if (!ft_redirect_fdin(cmd))
			return (0);
	}
	if (cmd->fd_out != -1)
	{
		if (!ft_redirect_fdout(cmd))
			return (0);
	}
	else
	{
		if (dup2(data->pipe[i % 2][1], STDOUT_FILENO) == -1)
			return (0);
	}
	ft_close_pipe(data->pipe[i % 2]);
	ft_close_redir_fds(data);
	return (1);
}
