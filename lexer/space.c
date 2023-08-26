/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:58:02 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/27 00:01:27 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Gere le caractere espace
*/
int	ft_space_separator(t_data *data, t_lexer **current, int *i)
{
	if (!data->loop)
		return (1);
	if ((*current)->str_type != NO_QUOTE)
		return (1);
	if (!ft_is_space(data->input[*i]))
		return (1);
	*current = ft_delimite(*current);
	if (!*current)
		return (0);
	if (!ft_add_char(*current, data->input[*i]))
		return (0);
	*current = ft_delimite(*current);
	if (!*current)
		return (0);
	data->loop = 0;
	return (1);
}

/*
	Quelles sont les caracteres considérées comme un espacement
*/
int	ft_is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c >= 9 && c <= 12)
		return (1);
	return (0);
}
