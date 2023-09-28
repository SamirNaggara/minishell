/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:36:51 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/27 21:54:31 by snaggara         ###   ########.fr       */
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
	int				new_arg;

	new_arg = 1;
	current_cmd = data->first_cmd;
	current_lexer = data->lexer;
	current_cmd->lexer = current_lexer;
	if (!ft_int_arg_tab(current_cmd, current_lexer))
		return (0);
	while (current_lexer)
	{
		if (!ft_add_arg_from_lexer(&new_arg, &current_cmd, &current_lexer))
			return (0);
		current_lexer = current_lexer->next;
	}
	return (1);
}

int	ft_add_arg_from_lexer(int *new_arg, t_simple_cmd **cmd, t_lexer **lexer)
{
	if ((*lexer)->operator == PIPE)
	{
		*cmd = (*cmd)->next;
		(*cmd)->lexer = (*lexer)->next;
		if (!ft_int_arg_tab(*cmd, (*lexer)->next))
			return (0);
	}
	else if (!ft_is_space_lexer(*lexer))
	{
		if (!ft_add_arg_to_cmd2(new_arg, *cmd, *lexer))
			return (0);
	}
	else if (ft_is_space_lexer(*lexer))
		*new_arg = 1;
	return (1);
}

int	ft_add_arg_to_cmd2(int *new_arg, t_simple_cmd *cmd, t_lexer *lexer)
{
	if (*new_arg)
	{
		if (!ft_add_arg_to_cmd(cmd, lexer->word))
			return (0);
		*new_arg = 0;
	}
	else
	{
		if (!ft_add_to_last_arg(cmd, lexer->word))
			return (0);
	}
	return (1);
}

int	ft_add_to_last_arg(t_simple_cmd *cmd, char *word)
{
	int		i;
	char	*new_arg;

	if (!cmd->cmd_args[0])
	{
		cmd->cmd_args[0] = ft_strdup(word);
		if (!cmd->cmd_args[0])
			return (0);
		return (1);
	}
	i = 0;
	while (cmd->cmd_args[i])
		i++;
	i--;
	new_arg = ft_strjoin(cmd->cmd_args[i], word);
	if (!new_arg)
		return (free(cmd->cmd_args[0]), 0);
	free(cmd->cmd_args[i]);
	cmd->cmd_args[i] = new_arg;
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
