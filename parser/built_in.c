/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:37:43 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/01 14:53:22 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Parcours la liste chaines des cmd, et remplis l'enum builtin
	avec la bonne valeur en fonction de la premiere commande
*/
void	ft_fill_built_in(t_data *data)
{
	t_simple_cmd	*current_cmd;

	current_cmd = data->first_cmd;
	while (current_cmd)
	{
		if (ft_is_same_word("exit", current_cmd->cmd_args[0]))
			current_cmd->builtin = EXIT;
		else if (ft_is_same_word("pwd", current_cmd->cmd_args[0]))
			current_cmd->builtin = PWD;
		// else if (ft_is_same_word("cd", current_cmd->cmd_args[0]))
		// 	current_cmd->builtin = CD;
		// else if (ft_is_same_word("export", current_cmd->cmd_args[0]))
		// 	current_cmd->builtin = EXPORT;
		// else if (ft_is_same_word("unset", current_cmd->cmd_args[0]))
		// 	current_cmd->builtin = UNSET;
		// else if (ft_is_same_word("env", current_cmd->cmd_args[0]))
		// 	current_cmd->builtin = ENV;
		// else if (ft_is_same_word("echo", current_cmd->cmd_args[0]))
		// 	current_cmd->builtin = ECHO;
		current_cmd = current_cmd->next;
	}

}
