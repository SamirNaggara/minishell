/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:10:45 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/03 21:13:41 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	executor(t_data *data)
// {
// 	// Create false command in structure
// 	t_simple_cmd	simple_cmd1;
// 	t_simple_cmd	simple_cmd2;
// 	t_simple_cmd	simple_cmd3;
// 	t_simple_cmd	simple_cmd4;
// 	t_simple_cmd	simple_cmd5;
// 	data->nb_cmd = 5;
// 	t_lexer			redirection1;
// 	t_lexer			redirection2;
// 	ft_fill_redirection1(&redirection1);
// 	ft_fill_redirection2(&redirection2);
// 	ft_fill_simple_cmd1(&simple_cmd1);
// 	simple_cmd1.redirections = &redirection1;
// 	ft_fill_simple_cmd2(&simple_cmd2);
// 	ft_fill_simple_cmd3(&simple_cmd3);
// 	ft_fill_simple_cmd4(&simple_cmd4);
// 	simple_cmd4.redirections = &redirection2;
// 	ft_fill_simple_cmd5(&simple_cmd5);
// 	simple_cmd1.next = &simple_cmd2;
// 	simple_cmd2.next = &simple_cmd3;
// 	simple_cmd3.next = &simple_cmd4;
// 	simple_cmd4.next = &simple_cmd5;
// 	data->first_cmd = &simple_cmd1;
// 	data->pipe[0][0] = -1;
// 	data->pipe[0][1] = -1;
// 	data->pipe[1][0] = -1;
// 	data->pipe[1][1] = -1;
// 	if (data->nb_cmd == 1)
// 	{
// 		if (!ft_exec_one_cmd(data))
// 			return (0);
// 	}
// 	if (!ft_create_all_process(data))
// 		return (0);
// 	ft_wait_children(data);
// 	ft_free_for_next_command(data);
// 	ft_free_path(data);
// 	return (1);
// }

int	executor(t_data *data)
{
	// t_simple_cmd	simple_cmd1;
	// t_lexer			redirection1;

	// ft_fill_simple_cmd1(&simple_cmd1);
	// ft_fill_redirection1(&redirection1);
	// simple_cmd1.redirections = &redirection1;
	// data->nb_cmd = 1;

	// data->first_cmd = &simple_cmd1;



	data->pipe[0][0] = -1;
	data->pipe[0][1] = -1;
	data->pipe[1][0] = -1;
	data->pipe[1][1] = -1;
	if (!ft_handle_here_docs(data))
		return (0);

	if (data->nb_cmd == 1)
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
	else if (data->nb_cmd > 1)
	{
		if (!ft_create_all_process(data))
			return (0);
	}
	ft_wait_children(data);
	ft_delete_here_doc_files(data);
	ft_free_for_next_command(data);
	ft_free_path(data); // A enlever plus tard
	return (1);
}