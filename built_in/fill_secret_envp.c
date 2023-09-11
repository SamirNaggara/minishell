/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_secret_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:25:20 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/10 18:25:31 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Cree une copie de la variable d'environnement du début
*/
int	ft_fill_secret_envp(t_data *data)
{
	int	i;
	int	size;

	size = ft_size_tab(data->envp);
	i = 0;
	data->secret_envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!data->secret_envp)
		return (0);
	while (data->envp[i])
	{
		data->secret_envp[i] = ft_strdup(data->envp[i]);
		if (!data->secret_envp[i])
			return (0);
		i++;
	}
	data->secret_envp[i] = NULL;
	return (1);
}