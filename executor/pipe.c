/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:14:22 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/25 00:11:56 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

void	ft_close_pipes(t_data *data)
{
	if (data->pipe[0][0] != -1)
		close(data->pipe[0][0]);
	if (data->pipe[0][1] != -1)
		close(data->pipe[0][1]);
	if (data->pipe[1][0] != -1)
		close(data->pipe[1][0]);
	if (data->pipe[1][1] != -1)
		close(data->pipe[1][1]);
}
