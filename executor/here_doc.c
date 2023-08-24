/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:37:03 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/25 00:13:26 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	Si on est dans le cas here doc
	il prends les infos du stdin et les mets dans un fichier temporaire
	Le fichier temporaire a pour nom TMP_FILE_NAME + le numero de 
	commande en cours, pour s'assurer que le fichier est toujours 
	unique meme s'il y a plusieurs here doc
*/
int	ft_handle_here_doc(t_simple_cmd *cmd, t_lexer *redirection)
{
	char	*stdin_line;
	char	*file_name;

	file_name = ft_create_here_doc_filename(cmd);
	if (!file_name)
		return (0);
	if (!ft_open_here_doc_file(cmd, file_name))
		return (0);
	stdin_line = get_next_line(STDIN_FILENO);
	while (!stdin_line || !ft_is_same_str(stdin_line, redirection->word))
	{
		write(cmd->fd_in, stdin_line, ft_strlen(stdin_line));
		free(stdin_line);
		stdin_line = get_next_line(STDIN_FILENO);
	}
	free(stdin_line);
	free(redirection->word);
	redirection->word = file_name;
	close(cmd->fd_in);
	return (1);
}

char	*ft_create_here_doc_filename(t_simple_cmd *cmd)
{
	char	*file_name;

	file_name = (char *)malloc(sizeof(char) * 30);
	if (!file_name)
		return (0);
	ft_strlcpy(file_name, TMP_FILE_NAME, 30);
	ft_strlcat(file_name, ft_itoa(cmd->index), 30);
	return (file_name);
}

int	ft_open_here_doc_file(t_simple_cmd *cmd, char *file_name)
{
	cmd->fd_in = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0655);
	if (!cmd->fd_in)
	{
		perror("Here doc not created properly");
		return (free(file_name), 0);
	}
	return (1);
}

void	ft_delete_here_doc_files(t_simple_cmd *cmd)
{
	t_lexer			*redirection;

	redirection = cmd->redirections;
	while (redirection)
	{
		if (!ft_strncmp(TMP_FILE_NAME, redirection->word, 19))
			unlink(redirection->word);
		redirection = redirection->next;
	}
}

int	ft_inf_inf_token(t_simple_cmd *cmd, t_lexer *redirection)
{
	if (redirection->token != INFINF)
		return (1);
	if (!ft_handle_here_doc(cmd, redirection))
		return (0);
	redirection->token = INF;
	return (1);
}
