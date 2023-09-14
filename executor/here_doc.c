/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:37:03 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 14:48:48 by snaggara         ###   ########.fr       */
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
		return (free(file_name), 0);
	stdin_line = get_next_line(STDIN_FILENO);
	while (!stdin_line || !ft_is_same_str(stdin_line, redirection->word))
	{
		if (g_global_state == 3)
			break ;
		if (!stdin_line)
		{
			fd_printf(STDERR_FILENO, "%s", E_SIG_HEREDOC);
			break ;
		}
		write(cmd->fd_in, stdin_line, ft_strlen(stdin_line));
		free(stdin_line);
		stdin_line = get_next_line(STDIN_FILENO);
	}
	if (!ft_end_handle_here_doc(cmd, redirection, stdin_line, file_name))
		return (0);
	return (1);
}

int	ft_end_handle_here_doc(t_simple_cmd *cmd, t_lexer *redirection,
			char *stdin_line, char *file_name)
{
	free(stdin_line);
	free(redirection->word);
	redirection->word = file_name;
	close(cmd->fd_in);
	if (g_global_state == 3)
		return (0);
	return (1);
}

char	*ft_create_here_doc_filename(t_simple_cmd *cmd)
{
	char	*file_name;
	char	*char_index;

	file_name = (char *)malloc(sizeof(char) * 30);
	if (!file_name)
		return (NULL);
	char_index = ft_itoa(cmd->index);
	if (!char_index)
		return (free(file_name), NULL);
	ft_strlcpy(file_name, TMP_FILE_NAME, 30);
	ft_strlcat(file_name, char_index, 30);
	free(char_index);
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
