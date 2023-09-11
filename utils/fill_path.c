/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:27:33 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/10 18:27:56 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_fill_path(t_data *data)
{
	char	*tmp_path;

	tmp_path = ft_add_slash(ft_found_replace_value(data, "PATH"));
	if (!tmp_path)
		return (0);
	data->paths = ft_split(tmp_path, ':');
	if (!data->paths)
		return (free(tmp_path), 0);
	free(tmp_path);
	return (1);
}