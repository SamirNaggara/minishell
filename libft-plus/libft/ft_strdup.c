/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 01:55:16 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/22 18:20:04 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	size;
	size_t	i;

	if (!s)
	{
		result = (char *)malloc(sizeof(char));
		result[0] = '\0';
		return (result);
	}
	size = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	ft_memset(result, 0, size + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	return (result);
}
// int main()
// {
//     char chaine[] = "voila";
//     char *resultat;

//     resultat = ft_strdup(chaine);
//     printf("%s\n", resultat);

//     free(resultat);
// }