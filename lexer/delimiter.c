/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:59:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/27 00:00:06 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Delimiter signifie que le mot ou la citation est fini
	Et que le caractere d'apres appartiendra 
	a un nouveau jeton
*/
t_lexer	*ft_delimite(t_lexer *lexer)
{
	t_lexer	*new;

	if (lexer->word == NULL)
		return (lexer);
	new = ft_begin_lexer();
	if (!new)
		return (NULL);
	lexer->next = new;
	new->prev = lexer;
	new->index = lexer->index + 1;
	return (new);
}

/*
	Ajoute un caractere dans le token en cours
*/
int	ft_add_char(t_lexer *current, char c)
{
	size_t	size;
	char	*new_word;

	if (!current->word)
	{
		current->word = (char *)malloc(sizeof(char) * 2);
		if (!current->word)
			return (0);
		current->word[0] = c;
		current->word[1] = '\0';
		return (1);
	}
	size = ft_strlen(current->word);
	new_word = (char *)malloc(sizeof(char) * (size + 2));
	if (!new_word)
		return (0);
	ft_strlcpy(new_word, current->word, size + 1);
	current->word[size] = c;
	current->word[size + 1] = '\0';
	return (1);
}
