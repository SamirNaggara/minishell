/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoigoux <sgoigoux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:55:39 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/16 14:59:10 by sgoigoux         ###   ########.fr       */
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
		return (data->exit_status = 0, 1);
	}
	if (data->nb_cmd != 1)
		return (data->exit_status = 0, 1);
	if (!ft_add_to_env(data, cmd))
		return (data->exit_status = 1, 0);
	return (data->exit_status = 0, 1);
}

/*
	Parmet d'ajouter une ligne dans les variables d'environnement
*/
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
		{
			key = ft_strdup(cmd->cmd_args[i]);
			if (!key)
				return (0);
		}
		if (!ft_isalpha(key[0]) && key[0] != '_')
		{
			ft_printf("Erreur : export: '%s' not a valid identifier\n", \
			cmd->cmd_args[i]);
			free(key);
			return (0);
		}
		if (!ft_add_one_export(data, key, cmd->cmd_args[i]))
		{
			free(key);
			return (0);
		}
		free(key);
		i++;
	}
	return (1);
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

/*
	Dans la chaine str il y a une expression key=value
	Cette fonction renvoie 1 si la clef est strictement identique
*/

int	ft_same_key(char *str, char const *key)
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
