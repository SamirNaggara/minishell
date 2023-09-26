/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:25:16 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/27 00:58:41 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_simple_cmd(t_data *data)
{
	t_simple_cmd	*browse;
	t_simple_cmd	*tmp;

	browse = data->first_cmd;
	if (!browse)
		return ;
	tmp = data->first_cmd;
	while (browse)
	{
		ft_free_lexer(browse->redirections);
		ft_free_double_tab(browse->cmd_args);
		browse = browse->next;
		free(tmp);
		tmp = browse;
	}
	data->first_cmd = NULL;
}

void	ft_free_lexer(t_lexer *lexer)
{
	t_lexer	*browse;
	t_lexer	*tmp;

	browse = lexer;
	tmp = lexer;
	while (browse)
	{
		free(browse->word);
		browse = browse->next;
		free(tmp);
		tmp = browse;
	}
}

void	ft_free_double_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_free_path(t_data *data)
{
	ft_free_double_tab(data->paths);
}

void	ft_free_for_next_command(t_data *data)
{
	if (data->child)
		free(data->child);
	ft_close_redir_fds(data);
	ft_free_simple_cmd(data);
}
