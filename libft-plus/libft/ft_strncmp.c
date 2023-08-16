/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:24:38 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/22 17:51:58 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	while (s1[i] && i < n)
	{
		diff = (int)((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (diff)
			return (diff);
		i++;
	}
	diff = (int)((unsigned char)s1[i] - (unsigned char)s2[i]);
	if (diff && i < n)
		return (diff);
	return (0);
}
/*
int	main(int ac, char **av)
{
	(void)ac;
	printf("%d\n", ft_strncmp(av[1], av[2], 10));
}
*/