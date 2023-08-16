/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_replace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:31:17 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 22:30:40 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

char	*c_replace(char *str, t_flag_list *flag, va_list *args, t_infos *infos)
{
	char	*to_return;
	char	car;
	size_t	i;

	ft_increment(infos);
	car = va_arg(*args, int);
	to_return = (char *)malloc(sizeof(char) * (*(infos->size) + 1));
	if (!to_return)
		return (NULL);
	i = 0;
	while (i < flag->length_flag)
	{
		to_return[i] = str[i];
		i++;
	}
	to_return[flag->length_flag] = car;
	i = 0;
	while (flag->length_flag + 1 + i < *(infos->size))
	{
		to_return[flag->length_flag + 1 + i] = str[flag->length_flag + 2 + i];
		i++;
	}
	to_return[*(infos->size)] = '\0';
	free(str);
	return (to_return);
}

void	ft_increment(t_infos *infos)
{
	*(infos->size) = *(infos->size) - 1;
	*(infos->prev) = *(infos->prev) + 1;
}
// a%cc\n        	Size = 5
// a0c\n   		    Size = 4
/*char	*c_replace(char *str, t_flag_list *flag,
// va_list *args, size_t *size, size_t *prev)
{
	char	*to_return;
	char	*tmp;
	char	car;

	*prev = *prev + 1;
	car = (char)va_arg(*args, int);
	if (car == '\0')
	{
		*size = *size - 1;
		return (str);
	}
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[0] = car;
	tmp[1] = '\0';
	to_return = replace_flag_by_str(str, flag, tmp, size);
	if (!to_return)
		return (NULL);
	free(tmp);
	return (to_return);
}
*/
