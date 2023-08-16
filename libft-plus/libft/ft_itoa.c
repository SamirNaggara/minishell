/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 00:46:32 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/23 15:13:55 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_len(int n);

char	*ft_initialise_result(long *number, size_t *i, size_t len);

int		ft_power2(int nb, int power);

char	*ft_itoa(int n)
{
	char	*result;
	long	number;
	size_t	i;
	size_t	len;

	i = 0;
	number = (long)n;
	len = (size_t)ft_get_len(number);
	result = ft_initialise_result(&number, &i, len);
	if (!result)
		return (NULL);
	while (len > 0)
	{
		result[i] = number / (ft_power(10, len - 1)) + '0';
		number = number % (ft_power(10, len - 1));
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_initialise_result(long *number, size_t *i, size_t len)
{
	char	*result;

	if (*number < 0)
	{
		result = (char *)malloc(sizeof(char) * (len + 2));
		if (!result)
			return (NULL);
		ft_memset(result, 0, len + 2);
		result[*i] = '-';
		*number = *number * -1;
		*i = *i + 1;
	}
	else
	{
		result = (char *)malloc(sizeof(char) * (len + 1));
		if (!result)
			return (NULL);
		ft_memset(result, 0, len + 1);
	}
	return (result);
}

size_t	ft_get_len(int n)
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

int	ft_power2(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	if (power == 2)
		return (nb * nb);
	return (nb * ft_power2(nb, power - 1));
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
