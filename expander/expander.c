/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:11:19 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/18 12:13:19 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Passe par le lexer
	Si il repere un $ dans une chaine de caractere
	Il regarde si il trouve une équivalence du mot
	Si il en trouve il le remplace
*/
int	ft_expander(t_data *data)
{
	t_lexer	*current_lexer;

	current_lexer = data->lexer;
	while (current_lexer)
	{
		if (!ft_should_replace(current_lexer))
		{
			current_lexer = current_lexer->next;
			continue ;
		}
		if (!ft_replace_dollar(data, &current_lexer->word))
			return (0);
		current_lexer = current_lexer->next;
	}
	return (1);
}

/*
	On regarde si le lexer actuel contient un $
	qu'il faudra apres remplacer
	Donc il faut que le lexer ne soit pas un operateur
	QUe le mot existe, qu'on ne soit pas en single quote

*/
int	ft_should_replace(t_lexer *lexer)
{
	char	*dollar;

	if (lexer->operator != NONE)
		return (0);
	if (lexer->str_type == SINGLE_QUOTE)
		return (0);
	if (!lexer->word)
		return (0);
	if (ft_is_space_lexer(lexer))
		return (0);
	dollar = ft_strchr(lexer->word, '$');
	if (!dollar)
		return (0);
	if (!dollar[1] || dollar[1] == ' ')
		return (0);
	if (ft_is_here_doc_file(lexer))
		return (0);
	return (1);
}

int	ft_is_here_doc_file(t_lexer *lexer)
{
	if (!lexer)
		return (0);
	if (!lexer->prev)
		return (0);
	if (lexer->prev->operator == INFINF)
		return (1);
	if (!lexer->prev->prev)
		return (0);
	if (lexer->prev->prev->operator == INFINF)
		return (1);
	return (0);
}
