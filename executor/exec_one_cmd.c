/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:12:43 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/26 20:12:00 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_one_cmd(t_data *data)
{
	ft_signal_reinit();
	if (!ft_malloc_child_pid(data))
		return (0);
	data->child[0] = fork();
	if (data->child[0] == -1)
		return (perror(E_CHILD), 0);
	if (data->child[0] == 0)
		ft_child_one_cmd(data);
	return (1);
}

int	ft_child_one_cmd(t_data *data)
{
	t_simple_cmd	*cmd;

	ft_here_doc();
	cmd = data->first_cmd;
	if (!ft_handle_here_docs(cmd))
		ft_exit_exec_one_cmd(data);
	ft_signal_slash_reinit();
	if (!ft_test_cmd_and_redirections(data, cmd))
		ft_exit_exec_one_cmd(data);
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
	ft_finish_child(data, cmd);
	exit(g_global_state);
	return (1);
}

void	ft_exit_exec_one_cmd(t_data *data)
{
	ft_close_redir_fds(data);
	ft_close_pipes(data);
	ft_free_for_next_command(data);
	exit(g_global_state);
}

int	ft_exec_without_fork(t_simple_cmd *cmd)
{
	if (cmd->builtin == EXIT)
		return (1);
	else if (cmd->builtin == CD)
		return (1);
	else if (cmd->builtin == EXPORT)
		return (1);
	else if (cmd->builtin == UNSET)
		return (1);
	return (0);
}

int	ft_exec_one_cmd_builtin(t_data *data)
{
	if (data->first_cmd->builtin == EXIT)
		ft_exit(data);
	else if (data->first_cmd->builtin == CD)
		ft_cd(data);
	else if (data->first_cmd->builtin == EXPORT)
		ft_export(data, data->first_cmd);
	else if (data->first_cmd->builtin == UNSET)
		ft_unset(data, data->first_cmd);
	return (1);
}
