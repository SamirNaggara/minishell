/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:58:01 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 15:07:47 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_redir(t_operator op)
{
	if (op >= 1 && op <= 4)
		return (1);
	return (0);
}

/*
	Si on a un operateur de redirection
	Alors on regarde si celui d'apres est valide (pas un operateur)
	Et alors on met dans le lexer en cours le mot de redirection
	Puis on met ce lexer dans la simple_cmd
	Puis on supprime la redirection du lexer
*/
int	ft_redir_in_simple_cmd(t_lexer *current_lexer, t_simple_cmd *current_cmd)
{
	if (current_lexer->operator == NONE || current_lexer->operator == PIPE)
		return (0);
	if (!ft_syntax_redirection(current_lexer))
		return (0);
	ft_add_in_cmd_redir(current_cmd, current_lexer);
	return (1);
}

/*
	Dans la simple cmd, il y a un t_lexer de redirection
	On rajoute notre redirection là, a la fin de la chaine
	Ceci est une copie, la chaine de lexer de base n'est pas impacté
	On note que le mot est le file_name, et l'operateur contient l'info
	de redirection
*/
int	ft_add_in_cmd_redir(t_simple_cmd *cmd, t_lexer *lexer)
{
	t_lexer	*browse;
	t_lexer	*new;

	new = ft_begin_lexer();
	if (!new)
		return (0);
	new->word = ft_get_redirection_file_name(lexer);
	if (!new->word)
		return (0);
	new->operator = lexer->operator;
	new->str_type = lexer->str_type;
	if (!cmd->redirections)
		cmd->redirections = new;
	else
	{
		browse = cmd->redirections;
		while (browse->next)
			browse = browse->next;
		new->index = browse->index + 1;
		new->prev = browse;
		new->next = NULL;
		browse->next = new;
	}
	return (1);
}

/*
	Va chercher le nom du fichier de redirection
*/
char	*ft_get_redirection_file_name(t_lexer *current_lexer)
{
	current_lexer = current_lexer->next;
	if (!ft_is_space_lexer(current_lexer))
		return (ft_strdup(current_lexer->word));
	return (ft_strdup(current_lexer->next->word));
}
