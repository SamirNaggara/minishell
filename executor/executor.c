/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:10:45 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/28 15:10:11 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	executor(t_data *data)
{
	ft_fill_path(data);
	ft_init_pipe(data);
	if (!ft_how_to_exec(data))
		return (ft_free_path(data), ft_free_for_next_command(data), 0);
	ft_wait_children(data);
	ft_delete_here_doc_files();
	ft_free_path(data);
	return (1);
}

/*
	Choisis comment sera executee la ou les commandes
	En fonction du no;ber de commande
	et de si c'est une builtin
*/
int	ft_how_to_exec(t_data *data)
{
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
				return (0);
		}
		else
		{
			if (!ft_exec_one_cmd(data))
				return (0);
		}
	}
	return (1);
}
