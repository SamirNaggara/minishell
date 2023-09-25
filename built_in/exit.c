/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:10:12 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/24 16:00:35 by sgoigoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    C'est la fonction appele lorsque l'utilisateur rentre la commande exit
    Attention, la commande doit tout free, ce qui n'est pas le cas la
*/

int	ft_any_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_data *data)
{
	t_simple_cmd	*cmd;
	int				i;

	cmd = data->first_cmd;
	i = 1;
	if (cmd->cmd_args[i])
	{
		if(!ft_check_error(data, cmd))
			return ;
	}
	ft_free_simple_cmd(data);
	ft_clean_lexer(data->lexer);
	if (data->secret_envp)
		ft_free_double_tab(data->secret_envp);
	if (data->paths)
		ft_free_double_tab(data->paths);
	free(data->input);
	ft_restore_terminal(data);
	exit(data->exit_status);
}

int	ft_check_error(t_data *data, t_simple_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd_args[i])
	{
		if (i >= 2)
		{
			data->exit_status = 1;
			fd_printf(STDERR_FILENO, "too many arguments\n");
			return (0);
		}
		i++;
	}
	i = 1;
	if (ft_any_number(cmd->cmd_args[i]))
		data->exit_status = ft_atoi(cmd->cmd_args[i]);
	else
	{
		data->exit_status = 2;
		fd_printf(STDERR_FILENO, "numeric argument required\n");
	}
	return (1);
}

void	ft_clean_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (lexer)
	{
		free(lexer->word);
		lexer = lexer->next;
		free(tmp);
		tmp = lexer;
	}
}
