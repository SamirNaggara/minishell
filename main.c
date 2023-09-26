/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:12:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/27 00:52:22 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global_state = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	data = (t_data){0};
	ft_memset(&data, 0, sizeof(data));
	ft_set_terminal_settings(&data);
	(void)ac;
	(void)av;
	data.envp = envp;
	ft_fill_secret_envp(&data);
	ft_minishell_loop(&data);
	ft_restore_terminal(&data);
	ft_free_double_tab(data.secret_envp);
	return (g_global_state);
}
