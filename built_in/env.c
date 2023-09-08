/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:03:47 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/06 15:03:59 by snaggara         ###   ########.fr       */
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
	while (data->secret_envp[i] && ft_strchr(data->secret_envp[i], '='))
		printf("%s\n", data->secret_envp[i++]);
}