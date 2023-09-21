/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 00:28:21 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/21 17:53:38 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		resultat;

	i = 0;
	sign = 1;
	resultat = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		resultat = resultat * 10 + nptr[i++] - '0';
	return (sign * resultat);
}
// int main(int ac, char **av)
// {
//     if (ac)
//     {
//         printf("%d\n", ft_atoi(av[1]));
//         printf("%d\n", atoi(av[1]));
//     }
// }
