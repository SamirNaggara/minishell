/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 01:42:42 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/22 17:51:19 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_len2(long n);

void	ft_putnbr_fd(int n, int fd)
{
	size_t	len;
	char	tmp;
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	len = (size_t)ft_get_len2(nb);
	while (len > 0)
	{
		tmp = nb / (ft_power(10, len - 1)) + '0';
		ft_putchar_fd(tmp, fd);
		nb = nb % (ft_power(10, len - 1));
		len--;
	}
}

size_t	ft_get_len2(long n)
{
	int		i;
	long	n_copy;

	n_copy = (long)n;
	if (n_copy < 0)
	n_copy = -n_copy;
	i = 1;
	while (n_copy >= 10)
	{
		n_copy = n_copy / 10;
		i++;
	}
	return ((size_t)i);
}

int	ft_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	if (power == 2)
		return (nb * nb);
	return (nb * ft_power(nb, power - 1));
}
