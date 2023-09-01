/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:36:51 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/01 13:37:03 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	On fait un deuxieme passage dans les cmds
	en creant le tableau de args
*/
int	ft_parse_cmds_arg(t_data *data)
{
	t_lexer			*current_lexer;
	t_simple_cmd	*current_cmd;

	current_cmd = data->first_cmd;
	current_lexer = data->lexer;
	current_cmd->lexer = current_lexer;
	if (!ft_int_arg_tab(current_cmd, current_lexer))
		return (0);
	
	while (current_lexer)
	{
		if (current_lexer->operator == PIPE)
		{
			current_cmd = current_cmd->next;
			current_cmd->lexer = current_lexer->next;
			if (!ft_int_arg_tab(current_cmd, current_lexer->next))
					return (0);
		}
		else if (!ft_is_space_lexer(current_lexer))
			ft_add_arg_to_cmd(current_cmd, current_lexer->word);
		current_lexer = current_lexer->next;
	}
	return (1);
}

int	ft_int_arg_tab(t_simple_cmd *cmd, t_lexer *lexer)
{
	int	i;
	int	size;

	i = 0;
	size = ft_count_args(lexer) + 1;
	cmd->cmd_args = (char **)malloc(sizeof(char *) * size);
	if (!cmd->cmd_args)
		return (0);
	while (i < size)
		cmd->cmd_args[i++] = NULL;
	return (1);
}

int	ft_add_arg_to_cmd(t_simple_cmd *cmd, char *arg)
{
	int	i;

	i = 0;
	while (cmd->cmd_args[i])
		i++;
	cmd->cmd_args[i] = arg;
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