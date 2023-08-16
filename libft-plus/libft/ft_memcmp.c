/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:34:19 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/21 01:08:43 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1bis;
	unsigned char	*s2bis;

	s1bis = (unsigned char *)s1;
	s2bis = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1bis[i] != s2bis[i])
			return (s1bis[i] - s2bis[i]);
		i++;
	}
	return (0);
}
// int main(int ac, char **av)
// {
//     if (ac)
//     {
//         printf("%d\n",ft_memcmp(av[1], av[2], atoi(av[3])));
//         printf("%d\n",memcmp(av[1], av[2], atoi(av[3])));

//     }
// }
