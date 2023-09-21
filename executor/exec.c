/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:30:11 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/21 17:09:42 by snaggara         ###   ########.fr       */
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

void	ft_free_path_before(char **path, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(path[j++]);
}

int	ft_cmd_valid(t_data *data, t_simple_cmd *cmd)
{
	int		i;
	char	*full_cmd;

	i = 0;
	if (cmd->builtin != NO_BUILTIN)
		return (1);
	while (data->paths && data->paths[i])
	{
		full_cmd = ft_strjoin(data->paths[i++], cmd->cmd_args[0]);
		if (!full_cmd)
			return (ft_free_path_before(data->paths, i), 0);
		if (access(full_cmd, X_OK) != -1)
			return (free(full_cmd), 1);
		free(full_cmd);
	}
	if (access(cmd->cmd_args[0], X_OK) != -1)
		return (1);
	fd_printf(STDERR_FILENO, E_CMD_NOT_FOUND, cmd->cmd_args[0]);
	data->exit_status = 127;
	return (0);
}
