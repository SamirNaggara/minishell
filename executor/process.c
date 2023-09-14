/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:45:53 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 14:58:09 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_create_all_process(t_data *data)
{
	int				i;
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

/*
	Attends tout les processus pour terminer avec un seul programme
	Si on est dans le cas ou on a pas fait de fork
	Alors on ne fait pas de wait
*/
void	ft_wait_children(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (data->nb_cmd == 1 && ft_exec_without_fork(data->first_cmd))
		return ;
	while (i < data->nb_cmd)
	{
		waitpid(data->child[i++], &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_status = WTERMSIG(status);
		if (ft_is_end_of_str(data->first_cmd->cmd_args[0], "/minishell"))
			ft_signal();
		ft_signal_slash_ignore();
	}
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
	if (data->child[0] > 1)
	{
		if (ft_is_end_of_str(data->first_cmd->cmd_args[0], "/minishell"))
			ft_signal_ignore();
	}
	if (i != 0)
		ft_close_pipe(data->pipe[(i - 1) % 2]);
}
