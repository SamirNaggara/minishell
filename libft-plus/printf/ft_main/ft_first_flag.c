/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:58:30 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 20:41:27 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

t_flag_list	*first_flag(t_flag_list **flag_list, const char *str, size_t *size,
			size_t *prev)
{
	t_flag_list	*browse;
	char		*ptr;

	ptr = str_search_percent(str, size, prev);
	if (!ptr)
		return (NULL);
	browse = *flag_list;
	while (browse)
	{
		if (browse->type == ptr[1])
		{
			browse->length_flag = ptr - str;
			*prev = browse->length_flag;
			return (browse);
		}
		browse = browse->next;
	}
	return (NULL);
}

char	*str_search_percent(const char *str, size_t *size, size_t *prev)
{
	size_t		i;
	char		*ptr;

	i = *prev;
	ptr = NULL;
	while (i < *size)
	{
		if (str[i] == '%')
		{
			ptr = (char *)str + i;
			break ;
		}
		i++;
	}
	return (ptr);
}
