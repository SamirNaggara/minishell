/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:26:37 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/26 16:52:22 by snaggara         ###   ########.fr       */
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
	if (!ft_handle_here_docs(browse))
	{
		ft_close_redir_fds(data);
		ft_close_pipes(data);
		ft_free_for_next_command(data);
		exit(g_global_state);
	}
	if (!ft_test_cmd_and_redirections(data, browse))
	{
		ft_close_redir_fds(data);
		ft_close_pipes(data);
		ft_free_for_next_command(data);
		exit(g_global_state);
	}
	if (!ft_discriminate_child(data, browse, i))
		return (perror(E_PIPE));
	ft_finish_child(data, browse);
	ft_free_lexer(browse->redirections);
	exit(g_global_state);
}

int	ft_discriminate_child(t_data *data, t_simple_cmd *cmd, int i)
{
	if (i == 0)
	{
		if (!ft_first_child(data, cmd, i))
			return (0);
	}
	else if (cmd->next)
	{
		if (!ft_middle_child(data, cmd, i))
			return (0);
	}
	else
	{
		if (!ft_last_child(data, cmd, i))
			return (0);
	}
	return (1);
}

void	ft_finish_child(t_data *data, t_simple_cmd *cmd)
{
	ft_close_redir_fds(data);
	if (cmd->builtin == PWD)
		ft_pwd();
	else if (cmd->builtin == ENV)
		ft_env(data);
	else if (cmd->builtin == EXPORT)
		ft_export(data, cmd);
	else if (cmd->builtin == ECHOO)
		ft_echo(data, cmd);
	else if (cmd->builtin == NO_BUILTIN)
		ft_exec_cmd(data, cmd);
}
