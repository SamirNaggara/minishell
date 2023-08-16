/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_replace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:24:48 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 22:41:40 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

char	*s_replace(char *str, t_flag_list *flag, va_list *args,
			t_infos *infos)
{
	char	*to_return;
	char	*arg;
	char	str_null[7];

	arg = va_arg(*args, char *);
	if (!arg)
	{
		ft_strlcpy(str_null, "(null)", 7);
		arg = str_null;
	}
	*(infos->prev) = *(infos->prev) + (size_t)ft_strlen(arg);
	to_return = replace_flag_by_str(str, flag, arg, infos->size);
	return (to_return);
}

char	*replace_flag_by_str(char *str, t_flag_list *flag, char *arg_str,
			size_t *size)
{
	size_t	i;
	size_t	j;
	char	*to_return;

	*size = *size - 2 + ft_strlen(arg_str);
	to_return = (char *)malloc(sizeof(char) * (*size + 1));
	if (!to_return)
		return (NULL);
	i = 0;
	j = 0;
	while (i < flag->length_flag)
		to_return[i++] = str[j++];
	j = 0;
	while (i < flag->length_flag + ft_strlen(arg_str))
		to_return[i++] = arg_str[j++];
	j = 0;
	while (i < *size)
		to_return[i++] = str[flag->length_flag + 2 + j++];
	to_return[i] = '\0';
	free(str);
	return (to_return);
}
