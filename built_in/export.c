/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:55:39 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/26 15:57:12 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Le builin export
*/
int	ft_export(t_data *data, t_simple_cmd *cmd)
{
	if (!cmd->cmd_args[1])
	{
		ft_print_all_export(data);
		return (g_global_state = 0, 1);
	}
	if (data->nb_cmd != 1)
		return (g_global_state = 0, 1);
	if (!ft_add_to_env(data, cmd))
		return (g_global_state = 1, 0);
	return (g_global_state = 0, 1);
}

/*
	Parmet d'ajouter une ligne dans les variables d'environnement
*/
int	ft_add_to_env(t_data *data, t_simple_cmd *cmd)
{
	char	*key;
	int		i;

	i = 1;
	while (cmd->cmd_args[i])
	{
		key = ft_key_from_arg(cmd, &i);
		if (!key)
			return (0);
		if (!ft_isalpha(key[0]) && key[0] != '_')
		{
			fd_printf(STDERR_FILENO, E_EXPORT_NVALID, cmd->cmd_args[i]);
			return (free(key), 0);
		}
		if (!ft_add_one_export(data, key, cmd->cmd_args[i]))
			return (free(key), 0);
		free(key);
		i++;
	}
	return (1);
}

char	*ft_key_from_arg(t_simple_cmd *cmd, int *i)
{
	char	*key;
	char	*equal;

	equal = ft_strchr(cmd->cmd_args[*i], '=');
	if (equal)
		key = ft_get_key(cmd->cmd_args[*i]);
	else
	{
		key = ft_strdup(cmd->cmd_args[*i]);
		if (!key)
			return (NULL);
	}
	return (key);
}

/*
	Pour obtenir juste la clef d'une chaine de caractere
	DOnc ce qui est devant le caractere =
	Ou toute la chaine si y'a pas d'egal
*/
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

/*
	Permet d'ajouter un element dans le secret_env
	En fonction de la clef et de la chaine entiere
	Pour le mettre a la bonne place
	Ou a la toute fin si la clef n'existe pas encore
*/
int	ft_add_one_export(t_data *data, char const *key, char *str)
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
	{
		free(data->secret_envp[i]);
		data->secret_envp[i] = ft_strdup(str);
		if (!data->secret_envp[i])
			return (0);
	}
	return (1);
}
