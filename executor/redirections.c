/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:24:58 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 14:02:51 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	On test la commande et les redirections
	Si y'a des erreurs, il faut quand meme tout tester
	Puis renvoyer si y'a une erreur ou pas
*/
int	ft_test_cmd_and_redirections(t_data *data, t_simple_cmd *cmd)
{
	int	status;

	status = 1;
	if (!ft_cmd_valid(data, cmd))
		status = 0;
	if (!ft_handle_redirection(data, cmd))
		status = 0;
	return (status);
}

/*
	Pour une structure de commande
	Pour chaque structure de redirection
	Si elle existe, on redirige vers une fonction
	Qui s'occupera de faire la bonne redirection
*/
int	ft_handle_redirection(t_data *data, t_simple_cmd *cmd)
{
	t_lexer	*redirection;

	if (!cmd->redirections)
		return (1);
	(void)data;
	redirection = cmd->redirections;
	while (redirection)
	{
		if (!ft_inf_operator(cmd, redirection))
			return (0);
		if (!ft_sup_operator(cmd, redirection))
			return (0);
		if (!ft_sup_sup_operator(cmd, redirection))
			return (0);
		redirection = redirection->next;
	}
	return (1);
}

/*
	Si l'operateur est >
	Alors il faut creer un fichier avec le nom contenu
	dans la structure de redirection
	Et le pas fermer le fichier tout de suite
*/
int	ft_sup_operator(t_simple_cmd *cmd, t_lexer *redirection)
{
	if (redirection->operator != SUP)
		return (1);
	cmd->fd_out = open(redirection->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
	{
		fd_printf(STDERR_FILENO, "%s: Permission denied\n", redirection->word);
		return (0);
	}
	return (1);
}

int	ft_sup_sup_operator(t_simple_cmd *cmd, t_lexer *redirection)
{
	if (redirection->operator != SUPSUP)
		return (1);
	cmd->fd_out = open(redirection->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd_out == -1)
	{
		fd_printf(STDERR_FILENO, "%s: Permission denied\n", redirection->word);
		return (0);
	}
	return (1);
}

int	ft_inf_operator(t_simple_cmd *cmd, t_lexer *redirection)
{
	if (redirection->operator != INF)
		return (1);
	cmd->fd_in = open(redirection->word, O_RDONLY, 0644);
	if (cmd->fd_in == -1)
	{
		fd_printf(STDERR_FILENO, "%s: Permission denied\n", redirection->word);
		return (0);
	}
	return (1);
}
