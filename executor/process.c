/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:45:53 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/21 14:37:26 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_create_all_process(t_data *data)
{
	int	i;
	t_simple_cmd	*browse;

	browse = data->first_cmd;
	i = 0;
	if (!ft_malloc_child_pid(data))
		return (0);
	while (browse != NULL)
	{
		ft_create_process(data, browse, i);
		browse = browse->next;
		i++;
	}
	return (1);
}

void	ft_wait_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
		waitpid(data->child[i++], NULL, 0);
}

int	ft_malloc_child_pid(t_data *data)
{
	data->child = (pid_t *)malloc(sizeof(pid_t) * data->nb_cmd);
	if (!data->child)
		return (0);
	return (1);
}

void	ft_create_process(t_data *data, t_simple_cmd *browse, int i)
{
	if (browse->next)
		pipe(data->pipe[i % 2]);
	
	data->child[i] = fork();
	if (data->child[i] == -1)
		return (perror(E_CHILD));
	if (data->child[i] == 0)
		ft_child(data, browse, i);
	if (i != 0)
		ft_close_pipe(data->pipe[(i - 1) % 2]);
}

// TO DO :
// - Tes fonctions childs ne prennent pas encore en compte les redirections !

// Tu prends en compte que si y'a stdin pour le premier ou le dernier enfant.
// Mais il faut que pour chaque noeud, s'il y a une redirections, que le dup soit fait par la
// - Il faut encore fermer tout les fichiers qui ont été ouvert

// Peut etre faire une fonction qui free toutes tes structures