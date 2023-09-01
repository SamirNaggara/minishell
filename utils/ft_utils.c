/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:28:43 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/01 13:34:17 by snaggara         ###   ########.fr       */
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