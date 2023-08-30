/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:25:16 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/30 12:55:54 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_simple_cmd(t_data *data)
{
	t_simple_cmd	*browse;

	browse = data->first_cmd;
	while (browse)
	{
		free(browse->cmd_args);
		ft_free_lexer(browse->redirections);
		browse = browse->next;
	}
}

void	ft_free_lexer(t_lexer *lexer)
{
	t_lexer	*browse;

	browse = lexer;
	while (browse)
	{
		free(browse->word);
		browse = browse->next;
	}
}

void	ft_free_double_tab(char **tab)
{
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

void	ft_free_path(t_data *data)
{
	ft_free_double_tab(data->paths);
	free(data->paths);
}

void	ft_free_for_next_command(t_data *data)
{
	ft_free_simple_cmd(data);
	free(data->child);
	ft_close_redir_fds(data);
}
