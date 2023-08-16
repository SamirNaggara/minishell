/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:07:59 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 22:46:39 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

t_infos	*ft_init_infos(void)
{
	t_infos	*infos;
	size_t	*size;
	size_t	*prev;

	infos = (t_infos *)malloc(sizeof(t_infos));
	if (!infos)
		return ((t_infos *)0);
	size = (size_t *)malloc(sizeof(size_t));
	if (!size)
	{
		free(infos);
		return ((t_infos *)0);
	}
	prev = (size_t *)malloc(sizeof(size_t));
	if (!prev)
	{
		free(size);
		free(infos);
		return ((t_infos *)0);
	}
	infos->size = size;
	infos->prev = prev;
	return (infos);
}

int	free_infos(t_infos *infos)
{
	free(infos->size);
	free(infos->prev);
	free(infos);
	return (0);
}

int	free_struct(t_flag_list **flag_list, t_infos *infos)
{
	ft_lstflag_clear(flag_list, free);
	free_infos(infos);
	free(flag_list);
	return (0);
}
