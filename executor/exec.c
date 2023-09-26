/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:30:11 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/26 18:24:25 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_cmd(t_data *data, t_simple_cmd *cmd)
{
	int		i;
	char	*full_cmd;

	i = 0;
	while (data->paths && data->paths[i])
	{
		full_cmd = ft_strjoin(data->paths[i], cmd->cmd_args[0]);
		if (!full_cmd)
			return (ft_free_path_before(data->paths, i), 0);
		execve(full_cmd, cmd->cmd_args, data->secret_envp);
		free(full_cmd);
		i++;
	}
	execve(cmd->cmd_args[0], cmd->cmd_args, data->secret_envp);
	perror("Command not found");
	return (1);
}

int	ft_cmd_valid(t_data *data, t_simple_cmd *cmd)
{
	int	i;
	int	test;

	if (!cmd->cmd_args[0])
		return (0);
	i = 0;
	if (cmd->builtin != NO_BUILTIN)
		return (1);
	test = ft_test_cmd(data, cmd, &i);
	if (test != 2)
		return (test);
	if (ft_is_directory(cmd->cmd_args[0]))
		return (g_global_state = 127, 0);
	if (ft_is_path_looking(cmd->cmd_args[0]))
	{
		if (access(cmd->cmd_args[0], X_OK) == -1)
			return (fd_printf(STDERR_FILENO, E_NO_FILE, cmd->cmd_args[0]), 0);
		return (1);
	}
	if (!data->paths)
		perror(cmd->cmd_args[0]);
	else
		fd_printf(STDERR_FILENO, E_CMD_NOT_FOUND, cmd->cmd_args[0]);
	return (g_global_state = 127, 0);
}

int	ft_test_cmd(t_data *data, t_simple_cmd *cmd, int *i)
{
	char	*full_cmd;

	while (data->paths && data->paths[*i])
	{
		full_cmd = ft_strjoin(data->paths[*i], cmd->cmd_args[0]);
		if (!full_cmd)
			return (ft_free_path_before(data->paths, *i), 0);
		if (access(full_cmd, X_OK) != -1)
			return (free(full_cmd), 1);
		(*i)++;
		free(full_cmd);
	}
	return (2);
}

int	ft_is_directory(char *path)
{
	struct stat	statbuf;

	if (ft_is_path_looking(path))
	{
		if (stat(path, &statbuf) != 0)
			return (0);
		if (S_ISDIR(statbuf.st_mode))
		{
			fd_printf(STDERR_FILENO, E_IS_DIR, path);
			return (1);
		}
		return (0);
	}
	if (stat(path, &statbuf) != 0)
	{
		return (0);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		fd_printf(STDERR_FILENO, E_CMD_NOT_FOUND, path);
		return (1);
	}
	return (0);
}
