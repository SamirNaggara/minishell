/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 00:43:15 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/22 01:00:31 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (size == 0 || nmemb == 0)
	{
		mem = malloc(0);
		return (mem);
	}
	if (size > 2147483647 || nmemb > 2147483647 || nmemb * size >= 2147483647)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, nmemb * size);
	return (mem);
}
