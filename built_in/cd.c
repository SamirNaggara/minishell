/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:34:54 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/03 20:37:15 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_data *data)
{
	char	*next_pwd;

	if (!data->first_cmd->cmd_args[1])
		return (0);
	if (!ft_test_dir(data->first_cmd->cmd_args[1]))
		return (0);
	next_pwd = ft_create_new_pwd(data);
	if (!next_pwd)
		return (0);
	// Changer le répertoire courant
	//printf("%s\n", pwd);
	//printf("%s\n", next_pwd);
	if (!ft_change_directory(data))
		return (0);

	if (!ft_update_oldpwd_envp(data))
		return (0);
	if (!ft_update_pwd_envp(data, next_pwd))
		return (0);
	free(next_pwd);
	return (1);
}

int	ft_test_dir(char *path)
{
	DIR *dir;

 	dir = opendir(path);
    if (!dir) {
        fd_printf(STDERR_FILENO, E_CD, path);
		return (0);
    }
	return (1);
}

int	ft_change_directory(t_data *data)
{
	if (chdir(data->first_cmd->cmd_args[1]) != 0) {
        perror("Chdir error : ");
        return (0);
    }
	return (1);
}

char	*ft_create_new_pwd(t_data *data)
{
	char	pwd[1024];
	char	*next_pwd;
	int	size;

	getcwd(pwd, 1024);
	size = ft_strlen(data->first_cmd->cmd_args[1]) + ft_strlen(pwd) + 1;
	next_pwd = (char *)malloc(sizeof(char) * size);
	if (!next_pwd)
		return (NULL);
	ft_bzero(next_pwd, size);
	ft_strlcpy(next_pwd, pwd, size);
	ft_strlcat(next_pwd, "/", size);
	ft_strlcat(next_pwd, data->first_cmd->cmd_args[1], size);
	return (next_pwd);
}
