/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:00:59 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/28 20:02:34 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Cette fonction s'occupe de supprimer les parties du lexer
	qu'on a mis dans simple cmd pour les redirections
	En les supprimant, elle s'assure que la chaine lexer reste coherente
	Soit c'est la fin et il suffit de supprimer (delete_end_of_lexer)
	Soit c'est pas la fin, et il faut relié ce qui est avant la redir
	avec ce qui est apres
	Si la redirection est dans le tout premier lexer, c'est un cas a part
	on ne peut pas utiliser de "before" comme les autres
	Donc on renvoie 1, et la boucle au dessus fera un continue
*/
int	ft_delete_redir_lexer(t_data *data, t_lexer **lexer)
{
	if (*lexer == data->lexer)
		return (ft_redir_is_first(data, lexer), -1);
	if (ft_delete_end_of_lexer(lexer))
		return (1);
	ft_delete_and_relink(lexer);
	return (1);
}

void	ft_redir_is_first(t_data *data, t_lexer **lexer)
{
	t_lexer	*new_begin;

	if (!ft_is_space_lexer((*lexer)->next))
			new_begin = (*lexer)->next->next;
	else
	{
		new_begin = (*lexer)->next->next->next;
		ft_free_lexer_node(&(*lexer)->next->next);
	}
	ft_free_lexer_node(&(*lexer)->next);
	ft_free_lexer_node(lexer);
	if (new_begin && ft_is_space_lexer(new_begin) && new_begin->next)
	{
		*lexer = new_begin->next;
		ft_free_lexer_node(&new_begin);
		new_begin = *lexer;
	}

	*lexer = new_begin;
	data->lexer = new_begin;
}

/*
	S'occupe du cas ou on supprime une redir dans le lexer
	Mais qu'il faut relink avec ce qui est apres
*/
void	ft_delete_and_relink(t_lexer **lexer)
{
	t_lexer	*before;
	t_lexer	*after;
	
	before = (*lexer)->prev;
	if (!ft_is_space_lexer((*lexer)->next))
		after = (*lexer)->next->next;
	else
	{
		after = (*lexer)->next->next->next;
		ft_free_lexer_node(&((*lexer)->next->next));
	}
	before->next = after;
	after->prev = before;
	ft_free_lexer_node(&((*lexer)->next));
	ft_free_lexer_node(lexer);
	if (after && ft_is_space_lexer(after))
	{
		before->next = after->next;
		if (after->next)
			after->next->prev = before;
		ft_free_lexer_node(&after);
	}
	*lexer = before;
}

/*
	Dans la redirection, si la redirection est la fin du lexer
	on free les derniers blocs
	et on arrete la chaine lexer plus tot
*/
int	ft_delete_end_of_lexer(t_lexer **lexer)
{
	t_lexer	*before;
	
	if (!(*lexer)->next->next)
	{
		(*lexer)->prev->next = NULL;
		before = (*lexer)->prev;
		ft_free_lexer_node(&(*lexer)->next);
		ft_free_lexer_node(&(*lexer));
		*lexer = before;
		return (1);
	}
	if (ft_is_space_lexer((*lexer)->next) && !(*lexer)->next->next->next)
	{
		(*lexer)->prev->next = NULL;
		before = (*lexer)->prev;
		ft_free_lexer_node(&(*lexer)->next->next);
		ft_free_lexer_node(&(*lexer)->next);
		ft_free_lexer_node(&(*lexer));
		*lexer = before;
		return (1);
	}
	return (0);
}