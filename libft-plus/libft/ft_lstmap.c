/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:16:37 by snaggara          #+#    #+#             */
/*   Updated: 2023/01/12 20:17:56 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*browse;
	t_list	*new_list;
	t_list	*result_f;

	if (!lst || !f)
		return ((t_list *) 0);
	browse = lst;
	new_list = NULL;
	while (browse != NULL)
	{
		result_f = ft_lstnew((*f)(browse->content));
		if (!result_f)
			return ((t_list *) 0);
		ft_lstadd_back(&new_list, result_f);
		browse = browse->next;
	}
	(void)del;
	return (new_list);
}
