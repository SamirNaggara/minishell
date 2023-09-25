/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:11:19 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/24 21:15:10 by snaggara         ###   ########.fr       */
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
		if (!ft_replace_dollar(data, current_lexer))
			return (0);
		current_lexer = current_lexer->next;
	}
	return (1);
}

/*
	State 0: On recopie juste la chaine
	State 1: On a ajoute un $, donc on parcours la chaine d'origine
	sans copier
	Jusqu'a croiser la fin du mot
*/
int	ft_replace_dollar(t_data *data, t_lexer *lexer)
{
	if (!lexer)
		return (1);
	if (!lexer->word)
		return (1);
	data->new_word = (char *)malloc(sizeof(char));
	if (!data->new_word)
		return (0);
	data->new_word[0] = '\0';
	if (!ft_expander_loop(data, lexer))
		return (free(lexer->word), 0);
	free(lexer->word);
	lexer->word = data->new_word;
	return (1);
}

int	ft_expander_loop(t_data *data, t_lexer *lexer)
{
	int		i;
	int		state;

	i = 0;
	state = 0;
	while (state != 2 && lexer->word[i])
	{
		if (state == 3)
			state = 0;
		if (!ft_expander_heart_loop(data, lexer, &state, &i))
			return (0);
		if (state < 2)
			i++;
	}
	return (1);
}

int	ft_expander_heart_loop(t_data *data, t_lexer *lexer, int *state, int *i)
{
	if (*state == 1)
		ft_end_of_dollar(lexer, state, i);
	else if (ft_is_expand_sign(lexer, state, i))
	{
		if (!ft_add_expand_word(data, state, i))
			return (0);
	}
	else if (*state == 0 && lexer->word[*i] == '$')
	{
		if (!ft_handle_expander(data, lexer, state, i))
			return (0);
	}
	else if (*state == 0)
	{
		data->new_word = ft_join_char(data->new_word, lexer->word[*i]);
		if (!data->new_word)
			return (0);
	}
	return (1);
}

// /*
// 	On regarde si le lexer actuel contient un $
// 	qu'il faudra apres remplacer
// 	Donc il faut que le lexer ne soit pas un operateur
// 	QUe le mot existe, qu'on ne soit pas en single quote

// */
// int	ft_should_replace(t_lexer *lexer)
// {
// 	char	*dollar;

// 	if (lexer->operator != NONE)
// 		return (0);
// 	if (lexer->str_type == SINGLE_QUOTE)
// 		return (0);
// 	if (!lexer->word)
// 		return (0);
// 	if (ft_is_space_lexer(lexer))
// 		return (0);
// 	dollar = ft_strchr(lexer->word, '$');
// 	if (!dollar)
// 		return (0);
// 	if (!dollar[1] || dollar[1] == ' ')
// 		return (0);
// 	if (ft_is_here_doc_file(lexer))
// 		return (0);
// 	return (1);
// }

// int	ft_is_here_doc_file(t_lexer *lexer)
// {
// 	if (!lexer)
// 		return (0);
// 	if (!lexer->prev)
// 		return (0);
// 	if (lexer->prev->operator == INFINF)
// 		return (1);
// 	if (!lexer->prev->prev)
// 		return (0);
// 	if (lexer->prev->prev->operator == INFINF)
// 		return (1);
// 	return (0);
// }

int	ft_char_is_stop_dollar(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '$')
		return (1);
	else if (c == '?')
		return (1);
	else if (c == '\'')
		return (1);
	else if (c == '"')
		return (1);
	else if (c == '=')
		return (1);
	else if (c == ':')
		return (1);
	return (0);
}
