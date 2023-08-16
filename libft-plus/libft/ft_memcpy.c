/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:33:56 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/22 17:34:28 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*srcbis;
	char		*destbis;

	srcbis = src;
	destbis = dest;
	i = 0;
	if ((src == NULL) && (dest == NULL))
	{
		destbis = NULL;
		return (destbis);
	}
	while (i < n)
	{
		destbis[i] = srcbis[i];
		i++;
	}
	return (destbis);
}
