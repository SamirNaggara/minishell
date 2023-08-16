/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:21:51 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/22 16:11:28 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *chaine);

int		char_in_array(const char car, const char *chaine);

char	*ft_beggining_pos(const char *s1, const char *set);

char	*ft_final_pos(const char *s1, const char *set);

char	*return_empty(void);

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	size;
	char	*pos_beg;
	char	*pos_final;
	char	*to_return;

	if (!set)
		return ((ft_strdup(s1)));
	if (!s1)
		return (NULL);
	if (!*s1)
		return (return_empty());
	pos_beg = ft_beggining_pos(s1, set);
	if (pos_beg == s1 + ft_strlen(s1))
		return (return_empty());
	pos_final = ft_final_pos(s1, set);
	size = pos_final - pos_beg + 1;
	to_return = (char *)malloc(sizeof(char) * (size + 1));
	if (!to_return)
		return (NULL);
	ft_memset(to_return, 0, size + 1);
	ft_strlcpy(to_return, pos_beg, size + 1);
	return (to_return);
}

char	*return_empty(void)
{
	char	*to_return;

	to_return = (char *)malloc(sizeof(char));
	if (!to_return)
		return (NULL);
	*to_return = '\0';
	return (to_return);
}
/*
	Renvoie la position du début de la chaine
*/

char	*ft_beggining_pos(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (!char_in_array(s1[i], set))
			break ;
		i++;
	}
	return ((char *)(s1 + i));
}

char	*ft_final_pos(const char *s1, const char *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (s1[i])
	{
		if (!char_in_array(s1[i], set))
			break ;
		i--;
	}
	return ((char *)(s1 + i));
}
/*
	Renvoie true si le caractere est dans la chaine
*/

int	char_in_array(const char car, const char *chaine)
{
	int	i;

	i = 0;
	while (chaine[i])
	{
		if (chaine[i++] == car)
			return (1);
	}
	return (0);
}
/*
int	main(int ac, char **av)
{
	(void)ac;
	char *result;

	result = ft_strtrim(av[1], av[2]);
	printf("%s\n", result);
	free(result);
	return 1;
}
*/