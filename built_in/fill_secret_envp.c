/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_secret_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:25:20 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/16 16:24:23 by snaggara         ###   ########.fr       */
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
	if (!ft_increment_shell_level(data))
		return (ft_free_double_tab(data->secret_envp), 0);
	if (!ft_add_pwd(data))
		return (ft_free_double_tab(data->secret_envp), 0);
	if (!ft_add_old_pwd(data))
		return (ft_free_double_tab(data->secret_envp), 0);
	return (1);
}

int	ft_add_old_pwd(t_data *data)
{
	if (ft_exist_in_secret_env(data, "OLDPWD"))
		return (1);
	if (!ft_add_one_envp(data, "OLDPWD"))
	{
		perror("getcwd failed");
		return (0);
	}
	return (1);
}

int	ft_exist_in_secret_env(t_data *data, char *key)
{
	int		i;
	char	*existing_key;

	i = 0;
	while (data->secret_envp && data->secret_envp[i])
	{
		existing_key = ft_get_key(data->secret_envp[i]);
		if (ft_is_same_word(existing_key, key))
			return (free(existing_key), 1);
		free(existing_key);
		i++;
	}
	return (0);
}


int	ft_add_pwd(t_data *data)
{
	char	*pwd;
	char	*full_line;
	
	pwd = getcwd(NULL, 0);
	if (!pwd) {
		perror("getcwd failed");
		return (0);
	}
	full_line = ft_strjoin("PWD=", pwd);
	if (!full_line)
	{
		free(pwd);
		perror("getcwd failed");
		return (0);
	}
	free(pwd);
	if (!ft_add_one_export(data, "PWD", full_line))
	{
		free(full_line);
		perror("getcwd failed");
		return (0);
	}
	free(full_line);
	return (1);
}

int	ft_increment_shell_level(t_data *data)
{
	char	*value;
	int		actual_lvl;
	char	*str_lvl;
	char	*full_str;

	value = ft_found_replace_value(data, "SHLVL");
	if (!value)
		return (0);
	actual_lvl = ft_atoi(value) + 1;
	free(value);
	str_lvl = ft_itoa(actual_lvl);
	if (!str_lvl)
		return (0);
	full_str = ft_strjoin("SHLVL=", str_lvl);
	if (!full_str)
		return (free(str_lvl), 0);
	free(str_lvl);
	if (!ft_add_one_export(data, "SHLVL", full_str))
		return (free(str_lvl), free(full_str), 0);
	free(full_str);
	return (1);
}
