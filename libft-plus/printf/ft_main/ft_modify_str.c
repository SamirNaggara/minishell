/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modify_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:17:19 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 22:21:25 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

char	*ft_modify_str(t_flag_list **flag_list, const char *str, va_list *args,
	t_infos *infos)
{
	t_flag_list	*flag;
	char		*to_return;

	*(infos->prev) = 0;
	to_return = (char *)ft_strdup(str);
	flag = first_flag(flag_list, to_return, infos->size, infos->prev);
	while (flag)
	{
		to_return = (*(flag->func_replace))(to_return, flag, args, infos);
		if (!to_return)
			return (NULL);
		flag = first_flag(flag_list, to_return, infos->size, infos->prev);
	}
	return (to_return);
}
// char	*handle_percent(char *str, size_t *size)
// {
// 	size_t	i;
// 	char	*to_return;

// 	i = 0;
// 	to_return = strdup(str);
// 	while (i < *size)
// 	{
// 		if (to_return[i] == '%' && to_return[i + 1] == '%')
// 			to_return = remove_one_char(to_return, i, size);
// 		i++;
// 	}
// 	free(str);
// 	return (to_return);
// }
/*
if (flag->type == 'c')
	to_return = c_replace(to_return, flag, args);
else if (flag->type == 's')
	to_return = s_replace(to_return, flag, args);
else if (flag->type == 'p')
	to_return = p_replace(to_return, flag, args);
else if (flag->type == 'd')
	to_return = d_replace(to_return, flag, args);
else if (flag->type == 'i')
	to_return = i_replace(to_return, flag, args);
else if (flag->type == 'u')
	to_return = u_replace(to_return, flag, args);
else if (flag->type == 'x')
	to_return = xup_replace(to_return, flag, args);
else if (flag->type == 'X')
	to_return = xup_replace(to_return, flag, args);
else if (flag->type == '%')
	to_return = c_replace(to_return, flag, args);
*/
