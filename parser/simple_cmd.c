/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:56:16 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/30 12:54:31 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Cette fonction ajoute une simple_cmd a la liste chainée
	Si on rencontre un pipe
*/
int	ft_add_cmd_if_pipe(t_simple_cmd **current_cmd, t_lexer *current_lexer)
{
	if (current_lexer->operator == PIPE)
	{
		*current_cmd = ft_add_one_simple_cmd(*current_cmd);
		if (!*current_cmd)
			return (0);
	}
	return (1);
}

t_simple_cmd	*ft_add_one_simple_cmd(t_simple_cmd	*current)
{
	t_simple_cmd	*new;

	new = ft_create_one_simple_cmd();
	if (!new)
		return (NULL);
	new->index = current->index + 1;
	current->next = new;
	return (new);
}

t_simple_cmd	*ft_create_one_simple_cmd()
{
	t_simple_cmd	*new;

	new = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!new)
		return (NULL);
	new->cmd_args = NULL;
	new->builtin = NO_BUILTIN;
	new->redirections = NULL;
	new->index = 0;
	new->fd_in = -1;
	new->fd_out = -1;
	new->next = NULL;
	return (new);
}

void	ft_visualise_cmd(t_data *data)
{
	t_simple_cmd	*current_cmd;
	t_lexer			*current_redirection;
	int				i;

	current_cmd = data->first_cmd;
	while (current_cmd)
	{
		printf("Voila une simple cmd : %d\n", current_cmd->index);
		current_redirection = current_cmd->redirections;

		while (current_redirection)
		{
			printf("	Redireciton file : %s\n", current_redirection->word);
			current_redirection = current_redirection->next;
		}
		i = 0;
		while (current_cmd->cmd_args && current_cmd->cmd_args[i])
		{
			printf("	Args %d : %s\n", i, current_cmd->cmd_args[i]);
			i++;
		}
		current_cmd = current_cmd->next;
	}
}
