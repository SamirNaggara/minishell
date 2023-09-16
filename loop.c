/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:13:20 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/16 16:37:02 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell_loop(t_data *data)
{
	while (1)
	{
		g_global_state = 0;
		data->input = read_input();
		if (!data->input)
			break ;
		if (!*data->input)
		{
			free(data->input);
			continue ;
		}
		data->full_cmd = ft_strdup(data->input);
		if (!data->full_cmd)
			return (0);
		add_history(data->full_cmd);
		if (!ft_lex_ex_parse(data))
			continue ;
		data->child = NULL;
		g_global_state = 1;
		executor(data);
		free(data->full_cmd);
		ft_clean_lexer(data->lexer);
		free(data->input);
	}
	return (1);
}

/*
	On utilise la fonction getcwd pour obtenir le chemin absolu
	du répertoire de travail actuel 
*/
char	*read_input(void)
{
	char	*ret;
	char	cwd[1024];

	ft_bzero(cwd, 1024);
	getcwd(cwd, sizeof(cwd));
	ft_strlcat(cwd, "  ", 1024);
	ret = readline(cwd);
	return (g_global_state = 0, ret);
}

/*
	Declenche le lexer, l'expander, puis le parseur
*/
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
