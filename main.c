/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:12:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/03 19:03:30 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*C'est mooooooooooooooooooche*/
int	main(int ac, char **av, char **envp)
{
	t_data	data;
	
	(void)ac;
	(void)av;
	data.envp = envp;
	ft_fill_secret_envp(&data);
	
	ft_minishell_loop(&data);

	return (0);
	
}

/*
	Cree une copie de la variable d'environnement du début
*/
int	ft_fill_secret_envp(t_data *data)
{
	int	i;
	int	size;

	size = ft_size_tab(data->envp);
	i = 0;
	data->secret_envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!data->secret_envp)
		return (0);
	while (data->envp[i])
	{
		data->secret_envp[i] = ft_strdup(data->envp[i]);
		if (!data->secret_envp[i])
			return (0);
		i++;
	}
	return (1);
}
/*
	Calcul la taille d'un tableau qui finit par null
*/
int	ft_size_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}

void	ft_minishell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline("Minishell ");
		if (!data->input)
			break ;
		if (!*data->input)
			continue ;
		if (!ft_lexer(data))
		{
			free(data->input);
			continue ;
		}

		if (!ft_parser(data))
		{
			free(data->input);
			continue ;
		}
		//ft_visualise_lexer(data);
		//ft_visualise_cmd(data);
		ft_fill_path(data);
		data->child = NULL;
		add_history(data->input);
		rl_redisplay();
		executor(data);
		free(data->input);
	}
}


// int	main(int ac, char **av, char **envp)
// {
// 	t_data			data;

// 	(void)ac;
// 	(void)av;

// 	ft_fill_path(&data);
// 	data.envp = envp;
// 	executor(&data);
// 	return (0);
// }

int	ft_fill_path(t_data *data)
{
	char	*tmp_path;

	tmp_path = ft_add_slash(getenv("PATH"));
	if (!tmp_path)
		return (0);
	data->paths = ft_split(tmp_path, ':');
	if (!data->paths)
		return (free(tmp_path), 0);
	free(tmp_path);
	return (1);
}
