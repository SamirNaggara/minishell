/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:10:45 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/16 17:45:47 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	executor(t_data *data)
{
	// Create false command in structure
	t_simple_cmd	simple_cmd1;
	t_simple_cmd	simple_cmd2;
	t_simple_cmd	simple_cmd3;
	t_simple_cmd	simple_cmd4;
	t_simple_cmd	simple_cmd5;

	ft_fill_simple_cmd1(&simple_cmd1);
	ft_fill_simple_cmd2(&simple_cmd2);
	ft_fill_simple_cmd3(&simple_cmd3);
	ft_fill_simple_cmd4(&simple_cmd4);
	ft_fill_simple_cmd5(&simple_cmd5);

	simple_cmd1.next = &simple_cmd2;
	simple_cmd2.next = &simple_cmd3;
	simple_cmd3.next = &simple_cmd4;
	simple_cmd4.next = &simple_cmd5;

	data->first_cmd = &simple_cmd1;
	// Beginning real fonction !
	if (!ft_create_pipes(data))
		return (0);
	if (!ft_create_all_process(data))
		return (0);
	ft_close_pipes(data);
	ft_wait_children(data);
	return (1);

}









