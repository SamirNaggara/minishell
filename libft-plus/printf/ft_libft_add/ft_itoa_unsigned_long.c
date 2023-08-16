/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned_long.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 00:46:32 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 22:48:53 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

char	*ft_itoa_long(unsigned int n)
{
	char						*result;
	unsigned long long			number;
	size_t						i;
	size_t						len;

	i = 0;
	number = (unsigned long long)n;
	len = (size_t)ft_get_len_lg(number);
	result = ft_initialise_result_lg(len);
	if (!result)
		return (NULL);
	while (len > 0)
	{
		result[i] = number / (ft_power5(10, len - 1)) + '0';
		number = number % (ft_power5(10, len - 1));
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_initialise_result_lg(unsigned long long len)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_memset(result, 0, len + 1);
	return (result);
}

unsigned long long	ft_get_len_lg(unsigned long long n)
{
	size_t				i;
	unsigned long long	n_copy;

	n_copy = (unsigned long long)n;
	i = 1;
	while (n_copy >= 10)
	{
		n_copy = n_copy / 10;
		i++;
	}
	return ((unsigned long long)i);
}

unsigned long long	ft_power5(unsigned long long nb, unsigned long long power)
{
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	if (power == 2)
		return (nb * nb);
	return (nb * ft_power5(nb, power - 1));
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
