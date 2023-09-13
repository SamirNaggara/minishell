/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:37:03 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/13 09:46:16 by snaggara         ###   ########.fr       */
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
	cmd->fd_in = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0655);
	if (!cmd->fd_in)
		return (perror(E_HERE_DOC), free(file_name), 0);
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

void	ft_delete_here_doc_files(t_data *data)
{
	t_lexer			*redirection;
	t_simple_cmd	*cmd;

	cmd = data->first_cmd;
	redirection = cmd->redirections;
	while (cmd)
	{
		redirection = cmd->redirections;
		while (redirection)
		{
			if (!ft_strncmp(TMP_FILE_NAME, redirection->word, 19))
				unlink(redirection->word);
			redirection = redirection->next;
		}
		cmd = cmd->next;
	}
}

int	ft_handle_here_docs(t_data *data)
{
	t_lexer			*redirection;
	t_simple_cmd	*cmd;

	cmd = data->first_cmd;
	while (cmd)
	{
		redirection = cmd->redirections;
		while (redirection)
			{
				if (!ft_inf_inf_operator(cmd, redirection))
					return (0);
				redirection = redirection->next;
			}
		cmd = cmd->next;
	}
	return (1);
}


