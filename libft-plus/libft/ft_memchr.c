/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:35:05 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/22 00:15:39 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sbis;

	sbis = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (sbis[i] == (unsigned char)(c % 256))
			return ((void *)(sbis + i));
		i++;
	}
	return ((void *)0);
}
/*
int main(int ac, char **argv)
{
    if (ac)
    {
        printf("%s",strchr(argv[1], *argv[2]));
    }
}
*/
