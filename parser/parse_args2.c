/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:00:22 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/20 18:00:24 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_add_arg_to_cmd(t_simple_cmd *cmd, char *arg)
{
	int	i;

	i = 0;
	while (cmd->cmd_args[i])
		i++;
	cmd->cmd_args[i] = ft_strdup(arg);
	if (!cmd->cmd_args[i])
		return (0);
	return (1);
}

/*
	On est en debut d'une nouvelle commande
	Compte le nombre d'argument qu'il y a dans a commande
	S'arrete lorsqu'il y a un pipe ou que c'est la fin
*/
int	ft_count_args(t_lexer *lexer)
{
	t_lexer	*current_lexer;
	int		count;

	if (!lexer)
		return (0);
	count = 0;
	current_lexer = lexer;
	while (current_lexer)
	{
		if (current_lexer->operator == PIPE)
			break ;
		if (!ft_is_space_lexer(current_lexer))
			count++;
		current_lexer = current_lexer->next;
	}
	return (count);
}
