/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:17:38 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/25 14:13:49 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_custom(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr_custom(const char *s, int c)
{
	int			i;
	int			size;

	if (!s || !*s)
		return (-1);
	size = (int)ft_strlen_custom(s);
	if (size > BUFFER_SIZE)
		i = size - BUFFER_SIZE;
	else
		i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlcpy_custom(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen_custom(src));
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		src[i] = '\0';
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen_custom(src));
}

char	*ft_strdup_custom(char *s)
{
	char	*result;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	if (!*s)
		return (NULL);
	size = ft_strlen_custom(s);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
	Join le premier dans le deuxieme et free accordingly
*/

char	*ft_strjoin_custom(char *line, char *tmp)
{
	char	*result;
	int		j;
	int		i;

	if (!line)
		return (tmp);
	result = malloc(sizeof(char)
			* (ft_strlen_custom(line) + ft_strlen_custom(tmp) + 1));
	if (!result)
	{
		free(tmp);
		return (NULL);
	}
	i = -1;
	while (line[++i])
		result[i] = line[i];
	j = 0;
	while (tmp[j])
		result[i++] = tmp[j++];
	result[i] = '\0';
	free(line);
	free(tmp);
	return (result);
}
