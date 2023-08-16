/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 01:42:27 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 22:48:23 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

char	*ft_itoa_hexa(unsigned long n)
{
	char	*result;
	long	number;
	size_t	i;
	size_t	len;

	i = 0;
	number = (unsigned long)n;
	len = ft_get_len3(number);
	result = ft_initialise_result3(len);
	if (!result)
		return (NULL);
	while (len > 0)
	{
		result[i] = "0123456789abcdef"[number / (ft_power3(16, len - 1))];
		number = number % (ft_power3(16, len - 1));
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_initialise_result3(size_t len)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_memset(result, 0, len + 1);
	return (result);
}

size_t	ft_get_len3(unsigned long n)
{
	long	i;
	long	n_copy;

	n_copy = (long)n;
	i = 1;
	while (n_copy >= 16)
	{
		n_copy = n_copy / 16;
		i++;
	}
	return ((size_t)i);
}

long	ft_power3(unsigned long nb, long power)
{
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	if (power == 2)
		return (nb * nb);
	return (nb * ft_power3(nb, power - 1));
}
/*
int main(int ac, char **av)
{
    char *result;

    result = ft_itoa(ft_atoi(av[1]));
    if (ac)
    {
        printf("ft itoi : %s\n", result);
        free(result);
    }
}
*/
