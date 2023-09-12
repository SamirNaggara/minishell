/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:35:10 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/01 13:36:57 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	On fait un premier passage qui créé le bon nombre
	de cmds en liste chainée
	Et qui place les redirections dans la liste
	Les redirections sont alors enlevés du lexer
*/
int	ft_parse_pipe_and_redir(t_data *data)
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
	return (1);
}

/*
	Renvoie le nombre de commande dans simple command
*/
int	ft_count_cmd(t_data *data)
{
	t_simple_cmd	*current_cmd;
	int	count;

	count = 0;
	current_cmd = data->first_cmd;
	while (current_cmd)
	{
		count++;
		current_cmd = current_cmd->next;
	}
	return (count);
}

/*
	Verifie qu'il n'y ai pas une commande sans arguments
	Si c'est le cas il renvoie une syntaxe error
	En gros c'est si y'a un pipe a la fin, alors pas valide
*/
int	ft_check_valids_cmds(t_data *data)
{
	t_lexer	*current_lexer;

	current_lexer = data->lexer;
	if (!current_lexer)
		return (1);
	while (current_lexer->next)
		current_lexer = current_lexer->next;
	if (!current_lexer)
		return (1);
	if (current_lexer->operator == PIPE)
		return (0);
	if (!ft_is_space_lexer(current_lexer))
		return (1);
	if (!current_lexer->prev)
		return (1);
	if (current_lexer->prev->operator == PIPE)
		return (0);
	return (1);
}

/*
	Check si la commande a bien des arguments
*/
int	ft_check_valid_cmd(t_simple_cmd *current_cmd)
{
	if (!current_cmd->cmd_args || !*current_cmd->cmd_args)
		return (0);
	return (1);
}