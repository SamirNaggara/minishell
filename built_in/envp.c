/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:35:09 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 14:24:08 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Permet de mettre a jour PWD dans le secret_env
*/
int	ft_update_pwd_envp(t_data *data, char *next_pwd)
{
	int		i;
	char	*pwd_line;
	int		size;

	size = ft_strlen(next_pwd) + 5;
	pwd_line = (char *)malloc(sizeof(char *) * size);
	if (!pwd_line)
		return (0);
	ft_strlcpy(pwd_line, "PWD=", 5);
	ft_strlcat(pwd_line, next_pwd, size);
	i = 0;
	while (data->secret_envp[i]
		&& ft_strncmp(data->secret_envp[i], "PWD=", 4) != 0)
		i++;
	if (!data->secret_envp[i])
		return (0);
	free(data->secret_envp[i]);
	data->secret_envp[i] = pwd_line;
	return (1);
}

/*
	Permet de mettre a jour OLDPWD dans le secret_env
*/
int	ft_update_oldpwd_envp(t_data *data)
{
	int		i;
	char	*pwd_line;
	int		size;
	char	pwd[1024];

	getcwd(pwd, 1024);
	size = ft_strlen(pwd) + 8;
	pwd_line = (char *)malloc(sizeof(char *) * size);
	if (!pwd_line)
		return (0);
	ft_strlcpy(pwd_line, "OLDPWD=", 8);
	ft_strlcat(pwd_line, pwd, size);
	i = 0;
	while (data->secret_envp[i]
		&& ft_strncmp(data->secret_envp[i], "OLDPWD=", 7) != 0)
		i++;
	if (!data->secret_envp[i])
		return (0);
	free(data->secret_envp[i]);
	data->secret_envp[i] = pwd_line;
	return (1);
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
