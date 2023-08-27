/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:54:24 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/27 19:04:46 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Reconnait le debut d'un opérateur,
	et donc délimite le mot d'avant
*/
int	ft_start_begin_op(t_data *data, t_lexer **current, int *i)
{
	if (!data->loop)
		return (1);
	if ((*current)->str_type != NO_QUOTE)
		return (1);
	if (!ft_is_beg_ope(data->input[*i]))
		return (1);
	*current = ft_delimite(*current);
	if (!*current)
		return (0);
	if (!ft_add_char(*current, data->input[*i]))
		return (0);
	data->loop = 0;
	return (1);
}

/*
	Si avant c'était un operateur,
	mais que là ça ne l'est plus
	Alors on delimite l'operateur
*/
int	ft_delimite_op(t_data *data, t_lexer **current, int *i)
{
	if (!data->loop)
		return (1);
	if (*i == 0)
		return (1);
	if ((*current)->str_type != NO_QUOTE)
		return (1);
	if (!ft_is_beg_ope(data->input[*i - 1]))
		return (1);
	if (ft_is_ope(data->input[*i - 1], data->input[*i]))
		return (1);
	*current = ft_delimite(*current);
	if (!*current)
		return (0);
	return (1);
}

/*
	On regarde si ce caractere, en s'alliant avec le precedent,
	peut former un operateur.
	Si c'est le cas, on l'ajoute au operator precedent,
	Puis on delimite le operator
	et on arrete la boucle
*/
int	ft_is_second_part_op(t_data *data, t_lexer **current, int *i)
{
	if (!data->loop)
		return (1);
	if (i == 0)
		return (1);
	if (!(*current)->word)
		return (1);
	if ((*current)->str_type != NO_QUOTE)
		return (1);
	if (!ft_is_beg_ope(data->input[*i - 1]))
		return (1);
	if (!ft_is_ope(data->input[*i - 1], data->input[*i]))
		return (1);
	if (!ft_add_char(*current, data->input[*i]))
		return (0);
	*current = ft_delimite(*current);
	if (!*current)
		return (0);
	data->loop = 0;
	return (1);
}

/*
	Si le caractere est le debut d'un operateur
*/
int	ft_is_beg_ope(char c)
{
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (c == '|')
		return (1);
	return (0);
}

int	ft_is_ope(char c1, char c2)
{
	if (c1 == '<' && c2 == '<')
		return (1);
	if (c1 == '<' && c2 == '<')
		return (1);
	return (0);
}
