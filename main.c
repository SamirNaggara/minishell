/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:12:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/23 12:17:59 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	t_data			data;

	(void)ac;
	(void)av;
	ft_fill_data(&data);
	data.envp = envp;
	executor(&data);
	return (0);
}

int	ft_fill_data(t_data *data)
{
	char	*tmp_path;

	tmp_path = ft_add_slash(getenv("PATH"));
	if (!tmp_path)
		return (0);
	data->paths = ft_split(tmp_path, ':');
	if (!data->paths)
		return (free(tmp_path), 0);
	data->nb_cmd = 5;
	free(tmp_path);
	return (1);
}

