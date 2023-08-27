/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:00:39 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/27 12:01:01 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Le but de cette fonction est de detecter les mots
	Qui sont des operateurs
	Et mettre l'opérateur approprié dans la structure
*/
void	ft_fill_lexer_ope(t_data *data)
{
	t_lexer	*current;

	current = data->lexer;
	while (current)
	{
		if (current->str_type == NO_QUOTE)
			ft_detect_operator(current);
		current = current->next;
	}
}
/*
	Detecte si un mot est exacement un operateur
	SI c'est le cas, on met l'enum correspondant dans operator
*/
void	ft_detect_operator(t_lexer *current)
{
	if (ft_strlen(current->word) > 2)
		return ;
	if (!current->word[0])
		return ;
	if (current->word[0] == '|' && !current->word[1])
		current->operator = PIPE;
	else if (current->word[0] == '<')
	{
		if (!current->word[1])
			current->operator = INF;
		if (current->word[1] == '<')
			current->operator = INFINF;
	}
	else if (current->word[0] == '>')
	{
		if (!current->word[1])
			current->operator = SUP;
		if (current->word[1] == '>')
			current->operator = SUPSUP;
	}
}