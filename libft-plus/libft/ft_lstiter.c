/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 01:34:10 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/21 20:25:02 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*browse;

	if (!lst || !f)
		return ;
	browse = lst;
	while (browse != NULL)
	{
		(*f)(browse->content);
		browse = browse->next;
	}
}
