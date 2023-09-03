/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:55:39 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/04 00:16:34 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_data *data, t_simple_cmd *cmd)
{
	if (!cmd->cmd_args[1])
	{
		ft_print_all_export(data);
		return (1);
	}
	if (data->nb_cmd != 1)
		return (1); 
	ft_add_to_env(data, cmd);
	return (1);
}

int	ft_add_to_env(t_data *data, t_simple_cmd *cmd)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(cmd->cmd_args[1], '=');
	if (!equal)
		return (0); // A changer
	key = ft_get_key(cmd->cmd_args[1]);
	if (!key)
		return (0);
	ft_add_one_export(data, key, cmd->cmd_args[1]);	
	return (1);
}


char	*ft_get_key(char *str)
{
	char	*to_return;
	int		i;

	i = 0;
	to_return = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		to_return[i] = str[i];
		i++;
		if (str[i - 1] == '=')
			break ;
	}
	to_return[i] = '\0';
	return (to_return);
		
}

int	ft_add_one_export(t_data *data, char *key, char *str)
{
	int	i;

	i = 0;
	while (data->secret_envp[i] && ft_strncmp(data->secret_envp[i], key, ft_strlen(key)))
		i++;
	if (!data->secret_envp[i])
	{
		if (!ft_add_one_envp(data, str))
			return (0);
		return (1);
	}
	data->secret_envp[i] = str;
	return (1);
}

int	ft_add_one_envp(t_data *data, char *str)
{
	int		size;
	char 	**new_envp;
	int		i;

	size = ft_size_tab(data->secret_envp);
	new_envp = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		return (0);
	while (data->secret_envp[i])
		i++;
	data->secret_envp[i++] = str;
	data->secret_envp[i] = NULL;
	return (1);
}

void	ft_print_all_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->secret_envp[i])
		ft_print_one_export(data->secret_envp[i++]);
}

void	ft_print_one_export(char *line)
{
	ft_printf("export %s\n", line);
}
