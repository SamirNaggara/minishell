/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:57:03 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 15:09:25 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	IL y a une erreur de syntaxe si
	Le caractere d'apres n'existe pas
	ou s'il existe mais que c'est le caractere d'apres qui n'existe pas
	OU bien si c'est un operateur
*/
int	ft_syntax_redirection(t_lexer *current_lexer)
{
	if (!current_lexer)
		return (ft_syntaxe_error('\n'), 0);
	if (!current_lexer->next)
		return (ft_syntaxe_error('\n'), 0);
	current_lexer = current_lexer->next;
	if (current_lexer->operator != NONE)
		return (ft_syntaxe_error(current_lexer->word[0]), 0);
	if (!ft_is_space_lexer(current_lexer))
		return (1);
	return (ft_syntax_redirection(current_lexer));
}

/*
	Affiche les erreurs de syntaxe
	Avec le caractere qui pose probleme
*/
void	ft_syntaxe_error(char const c)
{
	fd_printf(STDERR_FILENO, E_SYNTAXE);
	if (c == '\n')
		fd_printf(STDERR_FILENO, "<< newline >>\n");
	else
		fd_printf(STDERR_FILENO, "<< %c >>\n", c);
}
