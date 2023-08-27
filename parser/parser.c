/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:48:58 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/27 18:14:44 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_parser(t_data *data)
// {
// 	if (!data->lexer)
// 		return (0);
// }

/*
	Ta mission si tu l'acceptes c'est de creer les structures contenant les commandes simples
	Pour l'instant, l'idée c'est de passer une premiere fois pour creer le bon nombre de commandes
	Puis ensuite de placer les redirections si y'en a, et de les retirer du lexer
	Ensuite de placer les commandes et les arguments
	Puis de reperer les builtins
	Puis voila
*/

// t_simple_cmd	*ft_create_one_simple_cmd()
// {
// 	t_simple_cmd	*new;

// 	new = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
// 	if (!new)
// 		return (NULL);
// 	new->cmd_args = NULL;
// 	new->builtin = NO_BUILTIN;
// 	new->redirections = NULL;
// 	new->index = 0;
// 	new->fd_in = -1;
// 	new->fd_out = -1;
// 	return (new);
// }
