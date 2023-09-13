/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:10:45 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/13 15:23:27 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	executor(t_data *data)
{

	if (!ft_fill_path(data))
		return (0);
		
	data->pipe[0][0] = -1;
	data->pipe[0][1] = -1;
	data->pipe[1][0] = -1;
	data->pipe[1][1] = -1;
	global_state = 2;
	if (!ft_handle_here_docs(data))
		return (ft_free_path(data),ft_free_for_next_command(data), 0);
	global_state = 1;
	if (data->nb_cmd > 1)
	{
		if (!ft_create_all_process(data))
			return (0);
	}
	else
	{
		if (ft_exec_without_fork(data->first_cmd))
		{
			if (!ft_exec_one_cmd_builtin(data))
				return (global_state = 0, 0);
		}
		else
		{
			if (!ft_exec_one_cmd(data))
				return (global_state = 0, 0);
		}
	}
	ft_wait_children(data);
	ft_delete_here_doc_files(data);
	ft_free_for_next_command(data);
	ft_free_path(data); // A enlever plus tard
	return (global_state = 0, 1);
}