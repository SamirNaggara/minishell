/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_replace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:31:55 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 22:22:51 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

char	*x_replace(char *str, t_flag_list *flag, va_list *args,
			t_infos *infos)
{
	char	*to_return;
	char	*number;

	number = ft_itoa_hexa(va_arg(*args, unsigned int));
	if (!number)
		return (NULL);
	*(infos->prev) = *(infos->prev) + (size_t)ft_strlen(number);
	to_return = replace_flag_by_str(str, flag, number, infos->size);
	free(number);
	return (to_return);
}
