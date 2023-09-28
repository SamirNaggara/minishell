/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:13:20 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/28 16:33:02 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell_loop(t_data *data)
{
	while (1)
	{
		ft_init_signal_loop();
		data->input = read_input(data);
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
		executor(data);
		ft_free_after_execute(data);
	}
	return (1);
}

void	ft_free_after_execute(t_data *data)
{
	free(data->full_cmd);
	ft_clean_lexer(data->lexer);
	ft_free_for_next_command(data);
	free(data->input);
}

//vérifie si le répertoire actuel est accessible
int	is_current_directory_accessible(void)
{
	char	cwd[1024];

	ft_bzero(cwd, sizeof(cwd));
	getcwd(cwd, 1024);
	if (!*cwd)
		return (0);
	return (1);
}

/*
	On utilise la fonction getcwd pour obtenir le chemin absolu
	du répertoire de travail actuel 

	Si le répertoire n'est pas accessible (effacé quand on y était par exemple)
	alors on retourne au précédent
*/
char	*read_input(t_data *data)
{
	char	*ret;
	char	cwd[1024];
	char	*home;

	while (!is_current_directory_accessible())
	{
		if (chdir("..") == -1)
		{
			home = ft_found_replace_value(data, "HOME");
			if (!home)
				return (NULL);
			if (chdir(home) == -1)
				chdir("/");
			free(home);
		}
	}
	ft_bzero(cwd, 1024);
	getcwd(cwd, sizeof(cwd));
	ft_strlcat(cwd, "  ", 1024);
	ret = readline(cwd);
	return (ret);
}

/*
	Declenche le lexer, l'expander, puis le parseur
*/
int	ft_lex_ex_parse(t_data *data)
{
	if (!ft_lexer(data))
		return (free(data->full_cmd), free(data->input), 0);
	if (!ft_expander(data))
	{
		free(data->full_cmd);
		ft_free_lexer(data->lexer);
		return (free(data->input), 0);
	}
	if (!ft_parser(data))
	{
		free(data->full_cmd);
		ft_free_lexer(data->lexer);
		return (free(data->input), 0);
	}
	return (1);
}
