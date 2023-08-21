/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:30:11 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/21 12:01:02 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_cmd(t_data *data, t_simple_cmd *cmd)
{
	int		i;
	char	*full_cmd;


	i = 0;
	while (data->paths[i])
	{
		full_cmd = ft_strjoin(data->paths[i++], cmd->cmd_args[0]);
		if (!full_cmd)
			return (0); // Some freeing to do
		execve(full_cmd, cmd->cmd_args, data->envp);
		free(full_cmd);
	}
	execve(cmd->cmd_args[0], cmd->cmd_args, NULL);
	perror("Command not found");
	// Some freeing to do
	return (1);
}

int	ft_cmd_valid(t_data *data, t_simple_cmd *cmd)
{
	int		i;
	char	*full_cmd;


	i = 0;
	while (data->paths[i])
	{
		full_cmd = ft_strjoin(data->paths[i++], cmd->cmd_args[0]);
		if (!full_cmd)
			return (0); // Some freeing to do
		if (access(full_cmd, X_OK) != -1)
		{
			free(full_cmd);
 			return (1);
		}
		free(full_cmd);
	}
	if (access(cmd->cmd_args[0], X_OK) != -1)
		return (1);

	fd_printf(STDERR_FILENO, "%s%s\n", E_CMD_NOT_FOUND, cmd->cmd_args[0]);

	return (0);
}