/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:12:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/10 19:58:34 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	
	ft_signal();
	(void)ac;
	(void)av;
	data.envp = envp;
	data.exit_status = 0;
	ft_fill_secret_envp(&data);
	ft_minishell_loop(&data);
	return (data.exit_status);
}

//On utilise la fonction getcwd pour obtenir le chemin absolu du répertoire de travail actuel 
char	*read_input(void)
{
	char	*ret;
	char	cwd[1024];
	char	*text;

	ft_bzero(cwd, 1024);
	getcwd(cwd, sizeof(cwd));
	ft_strlcat(cwd, "\x1b[31m \u2665 \x1b[0m", 1024);
	text = ft_strjoin("\x1b[92m", cwd);
	if (!text)
		return (0);
	ret = readline(text);
	free(text);
	return (ret);
}


int	ft_minishell_loop(t_data *data)
{
	while (1)
	{
		data->input = read_input();
		if (!data->input)
			break ;
		if (!*data->input)
			continue ;
		data->full_cmd = ft_strdup(data->input);
		if (!data->full_cmd)
			return (0);
		if (!ft_lex_ex_parse(data))
			continue ;
		add_history(data->full_cmd);
		rl_redisplay();
		data->child = NULL;
		if (!executor(data))
			return (0);
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
	if (!ft_parser(data))
		return (free(data->input), 0);
	return (1);
}
