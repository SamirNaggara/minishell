/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:57:33 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/27 00:01:11 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	On fait une boucle sur chaque caractere.
	En fonction de ce qu'on a, on va remplir la structure chainéee
	lexer avec les infos pertinentes
*/
int	ft_lexer(t_data *data)
{
	int		i;
	t_lexer	*current;

	i = 0;
	current = ft_begin_lexer();
	data->lexer = current;
	if (!current)
		return (0);
	while (1)
	{
		data->loop = 1;
		if (current->str_type == NO_QUOTE && !data->input[i])
			break ;
		if (!ft_lexer_in_loop(data, &current, &i))
			return (0);
		if (data->loop)
			ft_add_char(current, data->input[i]);
		i++;
	}
	return (1);
}

/*
	On est dans la boucle.
	data->loop dis quand la le travail pour ce caractere est fait
	et qu'il n'est plus necessaire de parcourir la boucle
	Si une fonction retourne 0 c'est qu'un malloc a echoué
*/
int	ft_lexer_in_loop(t_data *data, t_lexer **current, int *i)
{
	if (!ft_quote_not_over(data, i))
		return (0);
	if (!ft_is_second_part_op(data, current, i))
		return (0);
	if (!ft_delimite_op(data, current, i))
		return (0);
	if (!ft_end_double_quote(data, current, i))
		return (0);
	if (!ft_end_single_quote(data, current, i))
		return (0);
	if (!ft_start_double_quote(data, current, i))
		return (0);
	if (!ft_start_single_quote(data, current, i))
		return (0);
	if (!ft_start_begin_op(data, current, i))
		return (0);
	if (!ft_space_separator(data, current, i))
		return (0);
	return (1);
}

t_lexer	*ft_begin_lexer(void)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->word = NULL;
	new->token = NONE;
	new->index = 0;
	new->str_type = NO_QUOTE;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
