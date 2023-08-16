/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:15:04 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/23 02:44:54 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del(void *content);

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*browse;
	t_list	*tmp;

	if (!lst || !*lst || !del)
		return ;
	browse = *lst;
	while (browse)
	{
		(*del)(browse->content);
		tmp = browse;
		browse = browse->next;
		free(tmp);
	}
	*lst = NULL;
}
/*
int	main()
{
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	t_list		*browse;

	char		str[] = "lorem";
	char		str2[] = "ipsum";
	char		str3[] = "dolor";
	char		str4[] = "retro";
	char	*to_display;

	elem = ft_lstnew(str);
	elem2 = ft_lstnew(str2);
	elem3 = ft_lstnew(str3);
	elem4 = ft_lstnew(str4);

	ft_lstadd_back(&elem, elem2);
	ft_lstadd_back(&elem, elem3);
	ft_lstadd_back(&elem, elem4);

	browse = elem;
	ft_lstclear(&elem, del);

	// while (browse)
	// {
	// 	to_display = (char *)browse->content;
	// 	printf("%s\n", to_display);
	// 	browse = browse->next;
	// }
}

void	del(void *content)
{
	free(content);
}
*/
