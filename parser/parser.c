/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:48:58 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/30 16:16:22 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_data *data)
{
	if (!ft_parse_pipe_and_redir(data))
		return (0);
	if (!ft_parse_cmds_arg(data))
		return (0);
	//ft_fill_built_in(data);
	data->nb_cmd = ft_count_cmd(data);
	return (1);
}

void	ft_fill_built_in(t_data *data)
{
	t_simple_cmd	*current_cmd;

	current_cmd = data->first_cmd;
	while (current_cmd)
	{
		if (ft_is_same_word("echo", current_cmd->cmd_args[0]))
			current_cmd->builtin = ECHO;
		else if (ft_is_same_word("cd", current_cmd->cmd_args[0]))
			current_cmd->builtin = CD;
		else if (ft_is_same_word("pwd", current_cmd->cmd_args[0]))
			current_cmd->builtin = PWD;
		else if (ft_is_same_word("export", current_cmd->cmd_args[0]))
			current_cmd->builtin = EXPORT;
		else if (ft_is_same_word("unset", current_cmd->cmd_args[0]))
			current_cmd->builtin = UNSET;
		else if (ft_is_same_word("env", current_cmd->cmd_args[0]))
			current_cmd->builtin = ENV;
		else if (ft_is_same_word("exit", current_cmd->cmd_args[0]))
			current_cmd->builtin = EXIT;
		current_cmd = current_cmd->next;
	}
}

int	ft_is_same_word(char const *s1, char const *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
	}
	if (s1[i] || s2[i])
		return (0);
	return (1);
}

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
