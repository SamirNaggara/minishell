/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:48:34 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/24 20:59:28 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_delete_here_doc_files(void)
{
	DIR				*dir;
	struct dirent	*file_name;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Erreur lors de l'ouverture du répertoire");
		return ;
	}
	file_name = readdir(dir);
	while (file_name)
	{
		if (strncmp(file_name->d_name, TMP_FILE_NAME, 18) == 0)
		{
			if (unlink(file_name->d_name) == -1)
				perror("Erreur lors de la suppression du fichier");
		}
		file_name = readdir(dir);
	}
	closedir(dir);
}

int	ft_handle_here_docs(t_simple_cmd *cmd)
{
	t_lexer			*redirection;

	redirection = cmd->redirections;
	while (redirection)
	{
		if (!ft_inf_inf_operator(cmd, redirection))
			return (0);
		redirection = redirection->next;
	}
	return (1);
}
