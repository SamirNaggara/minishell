/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:12:43 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 17:38:50 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_one_cmd(t_data *data)
{
	ft_signal_slash();
	if (!ft_malloc_child_pid(data))
		return (0);
	data->child[0] = fork();
	if (data->child[0] == -1)
		return (perror(E_CHILD), 0);
	if (data->child[0] == 0)
		ft_child_one_cmd(data);
	if (data->child[0] > 1)
	{
		if (ft_is_end_of_str(data->first_cmd->cmd_args[0], "/minishell"))
		{
			ft_signal_ignore();
			ft_signal_slash_ignore();
		}
	}
	return (1);
}

int	ft_child_one_cmd(t_data *data)
{
	t_simple_cmd	*cmd;

	cmd = data->first_cmd;
	if (!ft_test_cmd_and_redirections(data, cmd))
	{
		ft_close_redir_fds(data);
		exit(data->exit_status);
	}
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
	return (1);
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
