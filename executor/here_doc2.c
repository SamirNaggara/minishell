/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:48:34 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 14:58:29 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
