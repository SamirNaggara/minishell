/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:06:08 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/05 14:23:11 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_data *data, t_simple_cmd *cmd)
{
	int	i;

	if (!cmd->cmd_args[1])
		return (0);
	i = 0;
	while (data->secret_envp[i] &&
		!ft_same_key(data->secret_envp[i], cmd->cmd_args[1]))
		i++;
	if (!ft_update_secret_env_without(data, i))
		return (0);
	return (1);
}

int	ft_update_secret_env_without(t_data *data, int skip)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * ft_size_tab(data->secret_envp));
	if (!new_env)
		return (0);
	while (data->secret_envp[i] && i != skip)
	{
		new_env[i] = data->secret_envp[i];
		i++;
	}
	new_env[i] = NULL;
	free(data->secret_envp);
	data->secret_envp = new_env;
	return (1);
}
