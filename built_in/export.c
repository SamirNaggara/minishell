/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:55:39 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/05 10:37:04 by snaggara         ###   ########.fr       */
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
	int		i;

	i = 1;
	while (cmd->cmd_args[i])
	{
		equal = ft_strchr(cmd->cmd_args[i], '=');
		if (equal)
			key = ft_get_key(cmd->cmd_args[i]);
		else
			key = cmd->cmd_args[i];
		ft_add_one_export(data, key, cmd->cmd_args[i]);	
		i++;
	}
	return (1);
}


char	*ft_get_key(char *str)
{
	char	*to_return;
	int		i;

	i = 0;
	to_return = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] && str[i] != '=')
	{
		to_return[i] = str[i];
		i++;
	}
	to_return[i] = '\0';
	return (to_return);
		
}

int	ft_add_one_export(t_data *data, char *key, char *str)
{
	int	i;

	i = 0;
	while (data->secret_envp[i] && !ft_same_key(data->secret_envp[i], key))
		i++;
	if (!data->secret_envp[i])
	{
		if (!ft_add_one_envp(data, str))
			return (0);
		return (1);
	}
	if (ft_strchr(str, '='))
		data->secret_envp[i] = str;
	return (1);
}

/*
	Dans la chaine str il y a une expression key=value
	Cette fonction renvoie 1 si la clef est strictement identique
*/

int	ft_same_key(char *str, char *key)
{
	int	size_key;

	size_key = ft_strlen(key);
	if (ft_strncmp(str, key, size_key) != 0)
		return (0);
	if (!str[size_key])
		return (1);
	if (str[size_key] == '=')
		return (1);
	return (0);
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
	i = 0;
	while (data->secret_envp[i])
	{
		new_envp[i] = data->secret_envp[i];
		i++;
	}
	new_envp[i++] = str;
	new_envp[i] = NULL;
	free(data->secret_envp);
	data->secret_envp = new_envp;
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
	int	i;

	i = 0;
	write(1, "export ", 7);
	while (line[i] && line[i] != '=')
		write(1, line + i++, 1);
	if (!line[i])
	{
		write(1, "\n", 1);
		return ;
	}
	write(1, line + i++, 1);
	write(1, "\"", 1);
	while (line[i])
		write(1, line + i++, 1);
	write(1, "\"", 1);
	write(1, "\n", 1);
}
