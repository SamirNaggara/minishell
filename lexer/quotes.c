/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:53:21 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/25 13:19:42 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Si c'est le debut d'une citation double quote
*/
int	ft_start_double_quote(t_data *data, t_lexer **current, int *i)
{
	if (!data->loop)
		return (1);
	if ((*current)->str_type != NO_QUOTE)
		return (1);
	if (data->input[*i] != '"')
		return (1);
	*current = ft_delimite(*current);
	if (!*current)
		return (0);
	(*current)->str_type = DOUBLE_QUOTE;
	data->loop = 0;
	return (1);
}

/*
	Si c'est le debut d'une citation simple quote
*/
int	ft_start_single_quote(t_data *data, t_lexer **current, int *i)
{
	if (!data->loop)
		return (1);
	if ((*current)->str_type != NO_QUOTE)
		return (1);
	if (data->input[*i] != '\'')
		return (1);
	*current = ft_delimite(*current);
	if (!*current)
		return (0);
	(*current)->str_type = SINGLE_QUOTE;
	data->loop = 0;
	return (1);
}

/*
	Si c'est la fin d'une citation simple quote
*/
int	ft_end_single_quote(t_data *data, t_lexer **current, int *i)
{
	if (!data->loop)
		return (1);
	if ((*current)->str_type != SINGLE_QUOTE)
		return (1);
	if (data->input[*i] != '\'')
		return (1);
	*current = ft_delimite(*current);
	if (!*current)
		return (0);
	(*current)->str_type = NO_QUOTE;
	data->loop = 0;
	return (1);
}

/*
	Si c'est la fin d'une citation double quote
*/
int	ft_end_double_quote(t_data *data, t_lexer **current, int *i)
{
	if (!data->loop)
		return (1);
	if ((*current)->str_type != DOUBLE_QUOTE)
		return (1);
	if (data->input[*i] != '"')
		return (1);
	*current = ft_delimite(*current);
	if (!*current)
		return (0);
	(*current)->str_type = NO_QUOTE;
	data->loop = 0;
	return (1);
}

/*
	Si a la fin la quote n'est pas encore fini
	Il nous faut refaire un readline pour demander la suite des infos
	Jusqu'a ce que ça se termine normalement
*/
int	ft_quote_not_over(t_data *data, int *i)
{
	char	*tmp;

	if (!data->input[*i])
	{
		*i = -1;
		data->loop = 0;
		tmp = ft_strdup(data->full_cmd);
		if (!tmp)
			return (0);
		free(data->full_cmd);
		free(data->input);
		data->input = readline(" -> ");
		if (!data->input)
			return (0);
		data->full_cmd = ft_strjoin(tmp, data->input);
		if (!data->full_cmd)
			return (0);
		free(tmp);
	}
	return (1);
}
