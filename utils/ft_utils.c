/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:28:43 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/10 19:54:55 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
	Si s1 et s2 sont 2 mots strictement identique
	renvoie true
*/
int	ft_is_same_word(char const *s1, char const *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] || s2[i])
		return (0);
	return (1);
}

/*
	La meme chose qu'au dessus en plus moche
	Mais aussi en considerant 10 comme un espacement
*/
int	ft_is_same_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if ((!str1[i] || str1[i] == 10) && (!str2[i] || str2[i] == 10))
		return (1);
	return (0);
}

/*
	Calcul la taille d'un tableau qui finit par null
*/
int	ft_size_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}

char	*ft_strdup_plus_n(const char *s)
{
	char	*result;
	size_t	size;
	size_t	i;

	size = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (size + 2));
	if (!result)
		return (NULL);
	ft_memset(result, 0, size + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\n';
	return (result);
}
