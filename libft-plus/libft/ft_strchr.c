/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:58:45 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/23 03:55:26 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s % 256 == c % 256)
			return ((char *)s);
		s++;
	}
	if (c % 256 == 0)
		return ((char *)s);
	return ((char *)0);
}
/*
int main(int ac, char **argv)
{
    if (ac)
    {
        printf("%s",ft_strchr(argv[1], *argv[2]));
    }
}
*/