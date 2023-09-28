/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:48:58 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/28 16:38:43 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_data *data)
{
	if (!data->lexer || !data->lexer->word)
		return (0);
	if (ft_is_space_lexer(data->lexer) && !data->lexer->next)
		return (0);
	if (!ft_parse_pipe_and_redir(data))
		return (ft_free_simple_cmd(data), 0);
	data->nb_cmd = ft_count_cmd(data);
	if (!ft_parse_cmds_arg(data))
		return (ft_free_simple_cmd(data), 0);
	if (!ft_check_valids_cmds(data))
		return (ft_free_simple_cmd(data), ft_syntaxe_error('|'), 0);
	ft_fill_built_in(data);
	return (1);
}
