/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:55:34 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 12:03:10 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_end_of_str(char *str, char *needle)
{
	char	*reverse_str;
	char	*reverse_needle;

	if (!str || !*str)
		return (0);
	if (!needle || !*needle)
		return (0);
	reverse_str = ft_reverse_str(str);
	if (!reverse_str)
		return (0);
	reverse_needle = ft_reverse_str(needle);
	if (!reverse_needle)
		return (free(reverse_str), 0);
	if (ft_strncmp(reverse_str, reverse_needle, ft_strlen(reverse_needle)) == 0)
		return (free(reverse_needle), free(reverse_str), 1);
	free(reverse_needle);
	free(reverse_str);
	return (0);
	
}

char	*ft_reverse_str(char *str)
{
	char	*reverse;
	int		i;
	int		j;

	reverse = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!reverse)
		return (NULL);
	i = ft_strlen(str) - 1;
	j = 0;
	while (str[i])
	{
		reverse[j++] = str[i--];
		if (i == -1)
			break ;
	}
	reverse[j] = '\0';
	return (reverse);
}