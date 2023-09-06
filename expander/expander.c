/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:11:19 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/06 15:53:37 by snaggara         ###   ########.fr       */
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
		if (ft_should_replace(current_lexer))
		{
			current_lexer = current_lexer->next;
			continue ;
		}
		if (!ft_replace_dollar(current_lexer->word))
			return (0);
		current_lexer = current_lexer->next;
	}
	return (1);
}

int	ft_replace_dollar(char *str)
{
	char	*dollar;
	char	*word;
	char	*replace_str;

	dollar = ft_strchr(str, '$');
	while (dollar)
	{
		word = ft_extract_word(dollar);
		replace_str = ft_found_replace_value(word);
		if (!ft_replace(str, dollar, replace_str))
			return (0);
		dollar = ft_strchr(str, '$');
	}
	return (1);
}

char	*ft_extract_word(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '$')
		return (NULL);
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;
	// Ici Samir tu dois extraire le mot
	// Donc faire une autre fonction qui va copier le mot
	// Et le renvoyer (avec malloc)
}

/*
	On regarde si le lexer actuel contient un $
	qu'il faudra apres remplacer
	Donc il faut que le lexer ne soit pas un operateur
	QUe le mot existe, qu'on ne soit pas en single quote

*/
int	ft_should_replace(t_lexer *lexer)
{
	if (lexer->operator != NONE)
		return (0);
	if (lexer->str_type == SINGLE_QUOTE)
		return (0);
	if (!lexer->word)
		return (0);
	if (ft_is_space_lexer(lexer))
		return (0);
	if (!ft_strchr(lexer->word, '$'))
		return (0);
	return (1);
}