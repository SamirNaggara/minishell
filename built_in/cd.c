/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:34:54 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/20 18:27:01 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_data *data)
{
	char	*dest_file;

	if (ft_size_tab(data->first_cmd->cmd_args) >= 3)
		return (fd_printf(STDERR_FILENO, E_CD_ARG), data->exit_status = 1, 0);
	if (data->first_cmd->cmd_args[1])
		dest_file = ft_strdup(data->first_cmd->cmd_args[1]);
	else
		dest_file = ft_found_replace_value(data, "HOME");
	if (!dest_file)
		return (0);
	if (!ft_test_dir(data, dest_file))
		return (free(dest_file), 0);
	if (!ft_change_directory(data, dest_file))
		return (free(dest_file), 0);
	if (!ft_update_oldpwd_envp(data))
		return (free(dest_file), 0);
	if (!ft_update_pwd_envp(data))
		return (free(dest_file), 0);
	return (free(dest_file), data->exit_status = 0, 1);
}

/*
	Test si un dossier existe ou non
*/
int	ft_test_dir(t_data *data, char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		fd_printf(STDERR_FILENO, E_CD, path);
		return (data->exit_status = 1, 0);
	}
	closedir(dir);
	return (1);
}

/*
	Permet de changer directement le directory avec chdir
	Normalement on a deja testé le dossier
	donc ça ne devrait pas echouer
*/
int	ft_change_directory(t_data *data, char *dest_file)
{
	if (chdir(dest_file) != 0)
	{
		perror("Chdir error : ");
		return (data->exit_status = 1, 0);
	}
	return (1);
}

/*
	Retourne le chemin absolue du nouveau dossier
*/
char	*ft_create_new_pwd(t_data *data, char *dest_file)
{
	char	pwd[1024];
	char	*next_pwd;
	int		size;

	getcwd(pwd, 1024);
	size = ft_strlen(dest_file) + ft_strlen(pwd) + 1;
	next_pwd = (char *)malloc(sizeof(char) * size);
	if (!next_pwd)
		return (data->exit_status = 1, NULL);
	ft_bzero(next_pwd, size);
	ft_strlcpy(next_pwd, pwd, size);
	ft_strlcat(next_pwd, "/", size);
	ft_strlcat(next_pwd, dest_file, size);
	return (next_pwd);
}
