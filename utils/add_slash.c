/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_slash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:42:53 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 15:12:15 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_add_slash(char *path)
{
	char	*to_return;
	int		i;
	int		j;

	to_return = (char *)malloc(sizeof(char)
			* (ft_strlen(path) + ft_nb_slash_to_add(path) + 1));
	if (!to_return)
		return (NULL);
	i = 0;
	j = 0;
	while (path[j])
	{
		if (path[j] == ':')
			to_return[i++] = '/';
		to_return[i++] = path[j++];
	}
	to_return[i] = '/';
	to_return[i + 1] = '\0';
	return (to_return);
}

int	ft_nb_slash_to_add(char *path)
{
	int	i;
	int	nb;

	if (!path || !*path)
		return (-1);
	nb = 1;
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
			nb++;
		i++;
	}
	return (nb);
}
