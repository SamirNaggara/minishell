/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:26:37 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/21 14:32:17 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Pour chaque enfant, il
		test la commande
		applique les redirections
		Renvoie vers l'execution approprié selon si c'est la premiere,
		milieu, ou derniere commande
*/
void	ft_child(t_data *data, t_simple_cmd *browse, int i)
{
	if (!ft_test_cmd_and_redirections(data, browse))
		exit(1);
	if (i == 0)
	{
		if (!ft_first_child(data, browse, i))
			return (perror(E_PIPE));
	}
	else if (browse->next)
	{
		if (!ft_middle_child(data, browse, i))
			return (perror(E_PIPE));
	}
	else
	{
		if (!ft_last_child(data, browse, i))
			return (perror(E_PIPE));
	}
	ft_exec_cmd(data, browse);
	exit(0);
}

/*
	SI c'est la derniere commande
		On prends le fd_in du pipe
		Le stdout est redirigé vers le fdout (stdout ou redir)
*/
int	ft_last_child(t_data *data, t_simple_cmd *cmd, int i)
{
	if (dup2(data->pipe[(i - 1) % 2][0], cmd->fd_in) == -1)
		return (0);
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (0);
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
	if (dup2(data->pipe[(i - 1) % 2][0], cmd->fd_in) == -1)
		return (0);
	if (dup2(data->pipe[i % 2][1], cmd->fd_out) == -1)
		return (0);
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
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (0);
	if (dup2(data->pipe[i % 2][1], cmd->fd_out) == -1)
		return (0);
	ft_close_pipe(data->pipe[i % 2]);
	return (1);
}