/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:27:29 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/25 00:09:16 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fill_redirection1(t_lexer *redirection)
{
	redirection->word = malloc(sizeof(char) * 11);
	ft_strlcpy(redirection->word, "L", 11);
	redirection->token = INFINF;
	redirection->index = 0;
	redirection->next = NULL;
	redirection->prev = NULL;
}

void	ft_fill_redirection2(t_lexer *redirection)
{
	redirection->word = malloc(sizeof(char) * 11);
	ft_strlcpy(redirection->word, "sortie.txt", 11);
	redirection->token = SUPSUP;
	redirection->index = 0;
	redirection->next = NULL;
	redirection->prev = NULL;
}
