/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:35:09 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/19 14:45:48 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Permet de mettre a jour PWD dans le secret_env
*/
int	ft_update_pwd_envp(t_data *data)
{
	char	*pwd_line;
	char	pwd[1024];

	if (!getcwd(pwd, 1024))
		return (perror("getcwd failed\n"), 0);
	pwd_line = ft_strjoin("PWD=", pwd);
	if (!pwd_line)
		return (0);
	if (!ft_add_one_export(data, "PWD", pwd_line))
		return (free(pwd_line), 0);
	return (free(pwd_line), 1);
}

/*
	Permet de mettre a jour OLDPWD dans le secret_env
*/
int	ft_update_oldpwd_envp(t_data *data)
{
	char	*oldpwd_value;
	char	*oldpwd_line;

	oldpwd_value = ft_found_replace_value(data, "PWD");
	if (!oldpwd_value)
		return (0);
	oldpwd_line = ft_strjoin("OLDPWD=", oldpwd_value);
	if (!oldpwd_line)
		return (free(oldpwd_value), 0);
	if (!ft_add_one_export(data, "OLDPWD", oldpwd_line))
		return (free(oldpwd_line), free(oldpwd_value), 0);
	return (free(oldpwd_line), free(oldpwd_value), 1);
}

/*
	Pour obternir la ligne PWD depuis le envp choisi
*/
char	*ft_get_pwd_from_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PWD=", 4) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_strdup(envp[i] + 4));
}
