/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:14:22 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/16 14:14:55 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_create_pipes(t_data *data)
{
	if (pipe(data->pipe1) == -1)
		return (0);
	if (pipe(data->pipe2) == -1)
		return (0);
	return (1);
}

void	ft_close_pipes(t_data *data)
{
	close(data->pipe1[0]);
	close(data->pipe1[1]);
	close(data->pipe2[0]);
	close(data->pipe2[1]);
}

void	ft_close_pipe1(t_data *data)
{
	close(data->pipe1[0]);
	close(data->pipe1[1]);
}

void	ft_close_pipe2(t_data *data)
{
	close(data->pipe2[0]);
	close(data->pipe2[1]);
}