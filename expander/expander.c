/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:11:19 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/24 16:00:09 by snaggara         ###   ########.fr       */
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
	int		i;
	int		state;
	char	*key;
	char	*value;
	char	*new_word;

	state = 0;
	if (!lexer)
		return (1);
	if (!lexer->word)
		return (1);
	i = 0;
	new_word = (char *)malloc(sizeof(char));
	if (!new_word)
		return (0);
	new_word[0] = '\0';
	while (lexer->word[i])
	{
		if (state == 1)
		{
			if (ft_char_is_stop_dollar(lexer->word[i]))
			{
				state = 0;
				continue ;
			}
			i++;
		}
		else if (state == 0 && lexer->word[i] == '$' &&
			lexer->word[i + 1] && lexer->word[i + 1] == '?')
		{
			new_word = ft_strjoin_custom(new_word, ft_itoa(data->exit_status));
			if (!new_word)
				return (free(value), 0);
			state = 1;
			i++;
		}
		else if (state == 0 && lexer->word[i] == '$')
		{
			if (!lexer->word[i + 1])
			{
				if ((lexer->next && lexer->next->str_type != NO_QUOTE))
					break ;
			}
			if (ft_is_just_dollar_char(lexer, lexer->word + i))
			{
				new_word = ft_join_char(new_word, lexer->word[i]);
				if (!new_word)
					return (0);
				i++;
				continue ;
			}
			key = ft_extract_word(lexer->word + i);
			if (!key)
				return (0);
			value = ft_found_replace_value(data, key);
			if (!value)
				return (free(key), 0);
			free(key);
			new_word = ft_strjoin_custom(new_word, value);
			if (!new_word)
				return (free(value), 0);
			state = 1;
		}
		else if (state == 0)
		{
			new_word = ft_join_char(new_word, lexer->word[i]);
			if (!new_word)
				return (0);
		}
		i++;
	}
	free(lexer->word);
	lexer->word = new_word;
	return (1);
}

int	ft_is_just_dollar_char(t_lexer *lexer, char *str)
{
	if (lexer->next)
		return (0);
	if (!str[1])
		return (1);
	if (ft_char_is_stop_dollar(str[1]))
		return (1);
	return (0);
}

char	*ft_extract_word(char *str)
{
	int		i;
	char	*word;

	if (!str || !*str)
		return (NULL);
	word = (char *)malloc(sizeof(char));
	if (!word)
		return (NULL);
	word[0] = '\0';
	i = 1;
	while (str[i] && !ft_char_is_stop_dollar(str[i]))
	{
		word = ft_join_char(word, str[i]);
		i++;
	}
	return (word);
}

char	*ft_join_char(char *str, char c)
{
	char	*new;
	int		size;
	int		i;

	i = 0;
	if (!str)
	{
		new = (char *)malloc(sizeof(char) * 2);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	size = ft_strlen(str) + 2;
	new = (char *)malloc(sizeof(char) * size);
	if (!new)
		return (0);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(str);
	return (new);
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
