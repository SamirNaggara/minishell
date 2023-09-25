/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:51:52 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/25 14:31:32 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_expander(t_data *data, t_lexer *lexer, int *state, int *i)
{
	if (!lexer->word[*i + 1])
	{
		if ((lexer->next && lexer->next->str_type != NO_QUOTE))
			*state = 2;
	}
	if (*state < 2 && ft_is_just_dollar_char(lexer, lexer->word + *i))
	{
		data->new_word = ft_join_char(data->new_word, lexer->word[*i]);
		if (!data->new_word)
			return (0);
		(*i)++;
		*state = 3;
	}
	if (!ft_add_value_word(data, lexer, state, i))
		return (0);
	return (1);
}

int	ft_add_value_word(t_data *data, t_lexer *lexer, int *state, int *i)
{
	char	*key;
	char	*value;

	if (*state < 2)
	{
		*state = 1;
		key = ft_extract_word(lexer->word + *i);
		if (!key)
			return (0);
		value = ft_found_replace_value(data, key);
		if (!value)
			return (free(key), 0);
		free(key);
		data->new_word = ft_strjoin_custom(data->new_word, value);
		if (!data->new_word)
			return (free(value), 0);
	}
	return (1);
}

int	ft_is_expand_sign(t_lexer *lexer, int *state, int *i)
{
	if (*state != 0)
		return (0);
	if (lexer->word[*i] != '$')
		return (0);
	if (!lexer->word[*i + 1])
		return (0);
	if (lexer->word[*i + 1] != '?')
		return (0);
	return (1);
}

void	ft_end_of_dollar(t_lexer *lexer, int *state, int *i)
{
	if (ft_char_is_stop_dollar(lexer->word[*i]))
		*state = 3;
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
