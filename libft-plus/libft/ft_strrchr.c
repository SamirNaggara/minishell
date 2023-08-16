/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:58:45 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/23 03:59:34 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*end;

	if (c % 256 == 0)
		return ((char *)(s + ft_strlen(s)));
	end = s + ft_strlen(s) - 1;
	while (end != s - 1)
	{
		if (*end == c % 256)
			return ((char *)end);
		end--;
	}
	return ((char *)0);
}
/*
int main(int ac, char **argv)
{
    if (ac)
    {
        printf("%s",ft_strrchr(argv[1], *argv[2]));
    }
}
*/