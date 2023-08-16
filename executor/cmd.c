/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:26:34 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/16 17:33:12 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Si premier processus
		On change rien au stdin
		On change le stdout sur le pipe 1
*/
int	ft_process_cmd_first(t_data *data, t_simple_cmd *cmd)
{
	ft_close_pipe2(data);
	close(data->pipe1[0]);
	if (dup2(data->pipe1[1], STDOUT_FILENO) == -1)
		return (0);
	close(data->pipe1[1]);
	if (!ft_exec_cmd(data, cmd))
		return (0);
	return (1);
}

/*
	Si process impair
		On recupere le stdin du pipe1 (entree 0)
		On renvoie le stdout sur le pipe2 (entree 1)
*/
int	ft_process_cmd_odd(t_data *data, t_simple_cmd *cmd)
{
	close(data->pipe1[1]);
	if (dup2(data->pipe1[0], STDIN_FILENO) == -1)
		return (0);
	close(data->pipe1[0]);
	close(data->pipe2[0]);
	if (dup2(data->pipe2[1], STDOUT_FILENO) == -1)
		return (0);
	close(data->pipe2[1]);
	if (!ft_exec_cmd(data, cmd))
		return (0);
	return (1);
}

/*
	Si process pair
		On recupere le stdin du pipe2 (entree 0)
		On renvoie le stdout sur le pipe1 (entree 1)
*/
int	ft_process_cmd_even(t_data *data, t_simple_cmd *cmd)
{
	close(data->pipe2[1]);
	if (dup2(data->pipe2[0], STDIN_FILENO) == -1)
		return (0);
	close(data->pipe2[0]);
	close(data->pipe1[0]);
	if (dup2(data->pipe1[1], STDOUT_FILENO) == -1)
		return (0);
	close(data->pipe1[1]);
	if (!ft_exec_cmd(data, cmd))
		return (0);
	return (1);
}

/*
	Si dernier processus impair
		On recupere le stdin du pipe1 (entree 0)
		Puis on laisse le stdout

*/
int	ft_process_cmd_odd_last(t_data *data, t_simple_cmd *cmd)
{
	close(data->pipe1[1]);
	if (dup2(data->pipe1[0], STDIN_FILENO) == -1)
		return (0);
	close(data->pipe1[0]);
	ft_close_pipe2(data);
	if (!ft_exec_cmd(data, cmd))
		return (0);
	return (1);
}

/*
	Si dernier processus pair
		On recupere le stdin du pipe2 (entree 0)
		Puis on laisse le stdout

*/
int	ft_process_cmd_even_last(t_data *data, t_simple_cmd *cmd)
{
	close(data->pipe2[1]);
	if (dup2(data->pipe2[0], STDIN_FILENO) == -1)
		return (0);
	close(data->pipe2[0]);
	ft_close_pipe1(data);
	if (!ft_exec_cmd(data, cmd))
		return (0);
	return (1);
}