/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:55:34 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/26 13:20:03 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_end_of_str(char *str, char *needle)
{
	char	*reverse_str;
	char	*reverse_needle;

	if (!str || !*str)
		return (0);
	if (!needle || !*needle)
		return (0);
	reverse_str = ft_reverse_str(str);
	if (!reverse_str)
		return (0);
	reverse_needle = ft_reverse_str(needle);
	if (!reverse_needle)
		return (free(reverse_str), 0);
	if (ft_strncmp(reverse_str, reverse_needle, ft_strlen(reverse_needle)) == 0)
		return (free(reverse_needle), free(reverse_str), 1);
	free(reverse_needle);
	free(reverse_str);
	return (0);
}

char	*ft_reverse_str(char *str)
{
	char	*reverse;
	int		i;
	int		j;

	reverse = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!reverse)
		return (NULL);
	i = ft_strlen(str) - 1;
	j = 0;
	while (str[i])
	{
		reverse[j++] = str[i--];
		if (i == -1)
			break ;
	}
	reverse[j] = '\0';
	return (reverse);
}

size_t	ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if ((!dest || !src))
		return (0);
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (!src)
		return (src_len);
	i = 0;
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

/*
	Dans la chaine str il y a une expression key=value
	Cette fonction renvoie 1 si la clef est strictement identique
*/

int	ft_same_key(char *str, char const *key)
{
	int	size_key;

	size_key = ft_strlen(key);
	if (ft_strncmp(str, key, size_key) != 0)
		return (0);
	if (!str[size_key])
		return (1);
	if (str[size_key] == '=')
		return (1);
	return (0);
}

long	ft_atoi_long(const char *nptr)
{
	size_t	i;
	int		sign;
	long	resultat;

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
