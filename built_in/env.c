/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:03:47 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 14:22:11 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Imprime le secret env
	Mais seulement si la variable a une valeur
	Donc s'il y a un egal dans l'exression
*/
void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->secret_envp[i])
	{
		if (ft_strchr(data->secret_envp[i], '='))
			printf("%s\n", data->secret_envp[i]);
		i++;
	}
	data->exit_status = 1;
	exit(data->exit_status);
}
