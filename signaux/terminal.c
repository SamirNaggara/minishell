/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:09:57 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/20 19:46:31 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Permet de passer en mode canonique, donc un 
	caractere a la fois
	Et de ne pas afficher les caracteres quand on fait
	control c, ou autre
*/
void	ft_set_terminal_settings(t_data *data)
{
	tcgetattr(STDIN_FILENO, &data->terminal);
	data->terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->terminal);
}

/*
	Restaure les parametres du terminal
*/
void	ft_restore_terminal(t_data *data)
{
	data->terminal.c_cc[VINTR] = 0x03;
	data->terminal.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->terminal);
}
