/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:08:38 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/24 21:12:00 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_path_before(char **path, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(path[j++]);
}

int	ft_is_path_looking(char *path)
{
	if (path[strlen(path) - 1] == '/')
		return (1);
	if (ft_strncmp(path, "./", 2) == 0)
		return (1);
	if (ft_strncmp(path, "../", 3) == 0)
		return (1);
	return (0);
}
