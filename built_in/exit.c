/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:10:12 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/13 22:23:20 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    C'est la fonction appele lorsque l'utilisateur rentre la commande exit
    Attention, la commande doit tout free, ce qui n'est pas le cas la
*/
void	ft_exit(t_data *data)
{
	ft_clean_lexer(data->lexer);
	ft_free_simple_cmd(data);
	if (data->secret_envp)
		ft_free_double_tab(data->secret_envp);
	if (data->paths)
		ft_free_double_tab(data->paths);
	free(data->input);
	data->terminal.c_cc[VINTR] = 0x03;
	data->terminal.c_lflag &= ~ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->terminal);
	
	exit(data->exit_status);
}

void    ft_clean_lexer(t_lexer *lexer)
{
	t_lexer *tmp;

	tmp = lexer;
	while (lexer)
	{
		free(lexer->word);
		lexer = lexer->next;
		free(tmp);
		tmp = lexer;
	}
}
