/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:12:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/13 23:48:59 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	global_state = 0;



int	ft_read_by_char(void)
{
	int		i;
	char	c;
	char	command[1024];

	i = 0;
	ft_bzero(command, 1024);
	while (1) {
		c = getchar();
        if (c == '\n') {
            ft_printf(STDIN_FILENO, "%s", command);
            ft_bzero(command, 1024);
            i = 0;
			break ;
        } 
		else
            command[i++] = c;
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	
	ft_set_terminal_settings(&data);

    // Your program logic here.

    // Restore the old attributes before exiting.


	ft_signal();
	(void)ac;
	(void)av;
	data.envp = envp;
	data.exit_status = 0;
	data.full_cmd = NULL;
	ft_fill_secret_envp(&data);
	ft_minishell_loop(&data);

	data.terminal.c_cc[VINTR] = 0x03;
	data.terminal.c_lflag &= ~ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &data.terminal);

	return (data.exit_status);
}

//On utilise la fonction getcwd pour obtenir le chemin absolu du répertoire de travail actuel 
char	*read_input()
{
	char	*ret;
	char	cwd[1024];

	ft_bzero(cwd, 1024);
	getcwd(cwd, sizeof(cwd));
	ft_strlcat(cwd, "  ", 1024);
	ret = readline(cwd);
	return (global_state = 0, ret);
}


int	ft_minishell_loop(t_data *data)
{
	while (1)
	{
		global_state = 0;
		data->input = read_input();
		if (!data->input)
			break ;
		if (!*data->input)
			continue ;
		data->full_cmd = ft_strdup(data->input);
		if (!data->full_cmd)
			return (0);
		add_history(data->full_cmd);
		if (!ft_lex_ex_parse(data))
			continue ;
		//ft_visualise_lexer(data);

		data->child = NULL;
		global_state = 1;
		executor(data);
		free(data->full_cmd);
		ft_clean_lexer(data->lexer);
		free(data->input);
	}
	return (1);
}

int	ft_lex_ex_parse(t_data *data)
{
	if (!ft_lexer(data))
		return (free(data->input), 0);
	if (!ft_expander(data))
		return (free(data->input), 0);
	//ft_visualise_lexer(data);
	if (!ft_parser(data))
		return (free(data->input), 0);
	//ft_visualise_lexer(data);
	//ft_visualise_cmd(data);
	return (1);
}
