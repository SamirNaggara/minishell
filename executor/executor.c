/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:10:45 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/23 13:52:37 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	executor(t_data *data)
{
	// Create false command in structure
	t_simple_cmd	simple_cmd1;
	t_simple_cmd	simple_cmd2;
	t_simple_cmd	simple_cmd3;
	t_simple_cmd	simple_cmd4;
	t_simple_cmd	simple_cmd5;

	t_lexer			redirection1;
	//t_lexer			redirection2;

	ft_fill_redirection1(&redirection1);
	//ft_fill_redirection2(&redirection2);

	ft_fill_simple_cmd1(&simple_cmd1);
	simple_cmd1.redirections = &redirection1;
	ft_fill_simple_cmd2(&simple_cmd2);

	ft_fill_simple_cmd3(&simple_cmd3);
	ft_fill_simple_cmd4(&simple_cmd4);
	//simple_cmd4.redirections = &redirection2;
	ft_fill_simple_cmd5(&simple_cmd5);

	simple_cmd1.next = &simple_cmd2;
	simple_cmd2.next = &simple_cmd3;
	simple_cmd3.next = &simple_cmd4;
	simple_cmd4.next = &simple_cmd5;

	data->first_cmd = &simple_cmd1;

	data->pipe[0][0] = -1;
	data->pipe[0][1] = -1;
	data->pipe[1][0] = -1;
	data->pipe[1][1] = -1;
	if (!ft_create_all_process(data))
		return (0);
	ft_wait_children(data);
	ft_free_for_next_command(data);
	ft_free_path(data); // A enlever plus tard
	return (1);

}

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









