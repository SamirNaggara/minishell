/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:31:17 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 22:42:00 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

char	*pc_replace(char *str, t_flag_list *flag, va_list *args, t_infos *infos)
{
	char	*to_return;

	*(infos->prev) = *(infos->prev) + 1;
	(void)args;
	to_return = remove_one_char(str, flag->length_flag, infos->size);
	return (to_return);
}

char	*remove_one_char(char *str, size_t pos, size_t *size)
{
	char	*to_return;
	size_t	i;

	*size = *size - 1;
	to_return = (char *)malloc(sizeof(char) * (*size + 1));
	if (!to_return)
		return (NULL);
	i = 0;
	while (i < pos)
	{
		to_return[i] = str[i];
		i++;
	}
	while (i < *size)
	{
		to_return[i] = str[i + 1];
		i++;
	}
	to_return[*size] = '\0';
	free(str);
	return (to_return);
}
