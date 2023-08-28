/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:01:48 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/28 20:02:44 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	On veut savoir quel sont les lexer qui sont remplis
	uniquement d'un espace non quoté
	(il sert a rien, a part dans le cas "echo")
*/
int	ft_is_space_lexer(t_lexer *lexer)
{
	if (lexer->str_type != NO_QUOTE)
		return 0;
	if (!ft_is_space(lexer->word[0]))
		return (0);
	if (lexer->word[1])
		return (0);
	return (1);
}

void	ft_free_lexer_node(t_lexer **lexer)
{
	if ((*lexer)->word)
		free((*lexer)->word);
	free(*lexer);
}
