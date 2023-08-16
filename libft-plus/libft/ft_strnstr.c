/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:37:22 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/21 01:40:50 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	if (len == 0)
		return ((char *)0);
	j = 0;
	while (big[j])
	{
		if (big[j] == *little)
		{
			i = 0;
			while (little[i] && big[j + i] == little[i] && i + j < len)
				i++;
			if (!little[i])
				return ((char *)(big + j));
		}
		j++;
	}
	return ((char *)0);
}

//Si 

// int main(int ac, char **av)
// {
//     (void)ac;
//     printf("%s\n", strnstr(av[1], av[2], *av[3]));
// }