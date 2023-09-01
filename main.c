/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:12:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/01 16:56:40 by snaggara         ###   ########.fr       */
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

	ft_minishell_loop(&data);

	return (0);
	
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
		ft_fill_data(data);
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

// 	ft_fill_data(&data);
// 	data.envp = envp;
// 	executor(&data);
// 	return (0);
// }

int	ft_fill_data(t_data *data)
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
