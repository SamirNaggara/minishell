/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:48:58 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/01 14:02:27 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_data *data)
{
	if (!ft_check_valids_cmds(data))
		return (ft_syntaxe_error('\n'), 0);
	if (!ft_parse_pipe_and_redir(data))
		return (0);
	if (!ft_parse_cmds_arg(data))
		return (0);
	ft_fill_built_in(data);
	data->nb_cmd = ft_count_cmd(data);
	return (1);
}
