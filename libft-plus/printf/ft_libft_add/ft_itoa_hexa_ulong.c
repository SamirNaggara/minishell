/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hexa_ulong.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 01:42:27 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/10 21:09:38 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

char	*ft_itoa_hexa_ulong(long long n)
{
	char	*result;
	long long	number;
	long long	i;
	long long	len;

	i = 0;
	number = (long long)n;
	len = ft_get_len4(number);
	result = ft_initialise_result4(len);
	if (!result)
		return (NULL);
	while (len > 0)
	{
		result[i] = "0123456789abcdef"[number / (ft_power4(16, len - 1))];
		number = number % (ft_power4(16, len - 1));
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_initialise_result4(long long len)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_memset(result, 0, len + 1);
	return (result);
}

long long	ft_get_len4(long long n)
{
	long long	i;
	long long	n_copy;

	n_copy = (long long)n;
	i = 1;
	while (n_copy >= 16)
	{
		n_copy = n_copy / 16;
		i++;
	}
	return ((long long)i);
}

long long	ft_power4(long long nb, long long power)
{
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	if (power == 2)
		return (nb * nb);
	return (nb * ft_power4(nb, power - 1));
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
