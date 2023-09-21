/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:16:19 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/21 17:55:57 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nb_c_in_string(char const *string, char const c);

char	**return_null(void);

char	**return_simple(char const *s, int nul);

void	add_zero_string(char *chaine, char c, char *debut_chaine);

int		ftab(char **result, char *chaine, char *debut_chaine, char *fin_chaine);

char	**ft_split(char const *s, char c)
{
	char	*chaine;
	char	*debut_chaine;
	char	*fin_chaine;
	char	**result;
	char	**debut_result;

	if (!s)
		return ((char **) NULL);
	if (!*s)
		return (return_simple(s, 1));
	if (c == 0)
		return (return_simple(s, 0));
	chaine = ft_strdup(s);
	if (!chaine)
		return ((char **) NULL);
	debut_chaine = chaine;
	fin_chaine = chaine + ft_strlen(chaine);
	result = (char **)malloc((nb_c_in_string(chaine, c) + 2) * sizeof(char *));
	if (!result)
		return ((char **) NULL);
	debut_result = result;
	add_zero_string(chaine, c, debut_chaine);
	if (!ftab(result, chaine, debut_chaine, fin_chaine))
		return (return_simple(s, 1));
	return (debut_result);
}

int	ftab(char **result, char *chaine, char *debut_chaine, char *fin_chaine)
{
	int	i;

	i = 0;
	while (chaine < fin_chaine)
	{
		if (!*chaine && chaine++)
			continue ;
		result[i] = ft_strdup(chaine);
		if (!result[i])
		{
			while (i-- >= 0)
				free(result[i]);
			free(debut_chaine);
			free(result);
			return (0);
		}
		chaine += ft_strlen(chaine);
		chaine++;
		i++;
	}
	result[i] = (char *) NULL;
	free(debut_chaine);
	return (1);
}

void	add_zero_string(char *chaine, char c, char *debut_chaine)
{
	char	*fin_chaine;

	fin_chaine = chaine + ft_strlen(chaine);
	while (chaine < fin_chaine)
	{
		while (*chaine == c)
			*(chaine++) = '\0';
		chaine = ft_strchr(chaine, c);
		if (!chaine)
			break ;
		while (*chaine == c)
			*(chaine++) = '\0';
	}
	chaine = debut_chaine;
}

char	**return_simple(char const *s, int nul)
{
	char	**result;

	if (nul == 1)
	{
		result = (char **)malloc(sizeof(char *));
		if (!result)
			return ((char **) NULL);
		result[0] = NULL;
		return (result);
	}
	else
	{
		result = (char **)malloc(sizeof(char *) * 2);
		if (!result)
			return ((char **) NULL);
		result[0] = ft_strdup(s);
		result[1] = NULL;
		return (result);
	}
}

int	nb_c_in_string(char const *string, char const c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (string[i] == c)
		i++;
	while (string[i])
	{
		if (string[i] == c)
		{
			while (string[i] == c)
			{
				if (!string[i])
					break ;
				i++;
			}
			if (!string[i])
				return (counter);
			counter++;
		}
		i++;
	}
	return (counter);
}
