/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:03:47 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/03 21:15:53 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->secret_envp[i])
		printf("%s\n", data->secret_envp[i++]);
}