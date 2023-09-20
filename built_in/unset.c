/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:06:08 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 21:48:13 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Le builtin unset
	Supprime un element de secret_env
*/
int	ft_unset(t_data *data, t_simple_cmd *cmd)
{
	int	i;
	int	j;

	j = 1;
	if (!cmd->cmd_args[1])
		return (data->exit_status = 0, 1);
	while (cmd->cmd_args[j])
	{
		i = 0;
		while (data->secret_envp[i]
			&& !ft_same_key(data->secret_envp[i], cmd->cmd_args[j]))
			i++;
		if (!data->secret_envp[i])
		{
			data->exit_status = 0;
			break ;
		}
		if (!ft_update_secret_env_without(data, i))
		{
			data->exit_status = 1;
			break ;
		}
		j++;
	}
	return (0);
}

/*
	Cette fonction recréé un secret env
	Mais sans en recopier un, le skip
	Ainsi, on a dans les fait supprimer un element
*/
int	ft_update_secret_env_without(t_data *data, int skip)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = (char **)malloc(sizeof(char *)
			* (ft_size_tab(data->secret_envp) + 1));
	if (!new_env)
		return (0);
	while (data->secret_envp[i])
	{
		if (i == skip)
		{
			i++;
			continue ;
		}
		new_env[j++] = data->secret_envp[i++];
	}
	new_env[j] = NULL;
	free(data->secret_envp[skip]);
	free(data->secret_envp);
	data->secret_envp = new_env;
	return (1);
}
