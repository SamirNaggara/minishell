/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:48:58 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/28 20:02:55 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_data *data)
{
	t_lexer			*current_lexer;
	t_simple_cmd	*current_cmd;

	if (!data->lexer)
		return (1);
	data->first_cmd = ft_create_one_simple_cmd();
	if (!data->first_cmd)
		return (0);
	current_cmd = data->first_cmd;
	current_lexer = data->lexer;
	while (current_lexer)
	{
		if (!ft_add_cmd_if_pipe(&current_cmd, current_lexer))
			return (0);
		if (ft_is_redir(current_lexer->operator))
		{
			if (!ft_redir_in_simple_cmd(current_lexer, current_cmd))
				return (0);
			if (ft_delete_redir_lexer(data, &current_lexer) == -1)
				continue ;
		}
		current_lexer = current_lexer->next;
	}
	ft_visualise_cmd(data);
	return (1);
}
