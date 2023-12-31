/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:10:12 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/28 16:44:58 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    C'est la fonction appele lorsque l'utilisateur rentre la commande exit
    Attention, la commande doit tout free, ce qui n'est pas le cas la
*/

void	ft_exit(t_data *data)
{
	t_simple_cmd	*cmd;
	int				i;

	cmd = data->first_cmd;
	i = 1;
	fd_printf(STDERR_FILENO, "exit\n");
	if (cmd->cmd_args[i])
	{
		if (!ft_check_error(data, cmd))
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
	exit(g_global_state);
}

int	ft_any_number(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	if (*str == '-')
		str++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (ft_strlen(str) > 19)
		return (0);
	else if (ft_strlen(str) == 19)
	{
		if (ft_strncmp(str, "9223372036854775807", 20) > 0)
			return (0);
	}
	return (1);
}

int	ft_check_error(t_data *data, t_simple_cmd *cmd)
{
	int	i;

	(void)data;
	if (ft_any_number(cmd->cmd_args[1]))
		g_global_state = ft_atoi_long(cmd->cmd_args[1]);
	else
	{
		g_global_state = 2;
		fd_printf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			cmd->cmd_args[1]);
		return (1);
	}
	i = 1;
	while (cmd->cmd_args[i])
	{
		if (i >= 2)
		{
			fd_printf(STDERR_FILENO, "exit: too many arguments\n");
			return (g_global_state = 1, 0);
		}
		i++;
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
