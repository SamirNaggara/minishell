/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:00:22 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/27 14:51:39 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_add_arg_to_cmd(t_simple_cmd *cmd, char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	while (cmd->cmd_args[i])
		i++;
	if (!ft_add_multiple_word_arg(cmd, arg, i))
		return (0);
	// cmd->cmd_args[i] = ft_strdup(arg);
	// if (!cmd->cmd_args[i])
	// 	return (0);
	return (1);
}

int	ft_add_multiple_word_arg(t_simple_cmd *cmd, char *arg, int i)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (ft_is_space(arg[j]) && (j == 0 || !ft_is_space(arg[j - 1])))
			i++;
		else if (ft_is_space(arg[j]))
			;
		else
		{
			cmd->cmd_args[i] = ft_charjoin(cmd->cmd_args[i], arg[j]);
			if (!cmd->cmd_args[i])
				return (0);
		}
		j++;
	}

	return (1);
}

char	*ft_charjoin(char *str, char c)
{
	char	*to_return;
	int		i;

	if (!str)
	{
		to_return = (char *)malloc(sizeof(char));
		if (!to_return)
			return (NULL);
		to_return[0] = c;
		to_return[1] = '\0';
		return (free(str), to_return);
	}
	i = 0;
	to_return = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!to_return)
			return (NULL);
	while (str[i])
	{
		to_return[i] = str[i];
		i++;
	}
	to_return[i] = c;
	to_return[i + 1] = '\0';

	return (free(str), to_return);
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
			count += ft_nb_words(current_lexer->word);
		current_lexer = current_lexer->next;
	}
	return (count);
}

int	ft_nb_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	if (!str)
		return (0);
	count = 1;
	while (str[i])
	{
		if (ft_is_space(str[i++]))
			count++;
	}
	return (count);
}
