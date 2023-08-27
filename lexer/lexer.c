/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:57:33 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/27 11:58:34 by snaggara         ###   ########.fr       */
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
	ft_fill_lexer_ope(data);
	return (1);
}

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
	new->operator = NONE;
	new->index = 0;
	new->str_type = NO_QUOTE;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_visualise_lexer(t_data *data)
{
	t_lexer	*browse;

	browse = data->lexer;
	printf("\nLe lexer : \n");
	while (browse)
	{
		printf("L'element %d : %s\n", browse->index, browse->word);
		// if (browse->operator != NONE)
		// 	printf("Operator : %d\n", browse->operator);
		browse = browse->next;
	}
}