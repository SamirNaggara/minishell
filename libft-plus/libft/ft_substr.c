/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:27:15 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/23 04:16:55 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char const *src, unsigned int n);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	size;

	if (!s)
		return (NULL);
	if (ft_strlen(s) > len)
		size = len;
	else
		size = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		size = 0;
	new_str = (char *)malloc((size + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memset(new_str, '\0', size + 1);
	if (start > ft_strlen(s))
		return (new_str);
	ft_strncpy(new_str, s + start, size);
	return (new_str);
}

char	*ft_strncpy(char *dest, char const *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// int	main()
// {
// 	char test[] = "Tripouille";
// 	char *resultat;

// 	resultat = ft_substr(test, 5, 3);
// 	printf("%s", resultat);

// 	free(resultat);
// }
