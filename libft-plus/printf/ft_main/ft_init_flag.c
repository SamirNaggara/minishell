/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:57:17 by snaggara          #+#    #+#             */
/*   Updated: 2022/12/27 16:48:25 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "../ft_printf.h"

t_flag_list	**create_flag_list(void)
{
	t_flag_list	**flags;

	flags = (t_flag_list **)malloc(sizeof(t_flag_list *));
	if (!flags)
		return ((t_flag_list **)0);
	*flags = ft_lst_flag_new('c', &c_replace);
	ft_lst_flag_add_back(flags, ft_lst_flag_new('s', &s_replace));
	ft_lst_flag_add_back(flags, ft_lst_flag_new('p', &p_replace));
	ft_lst_flag_add_back(flags, ft_lst_flag_new('d', &d_replace));
	ft_lst_flag_add_back(flags, ft_lst_flag_new('i', &i_replace));
	ft_lst_flag_add_back(flags, ft_lst_flag_new('u', &u_replace));
	ft_lst_flag_add_back(flags, ft_lst_flag_new('x', &x_replace));
	ft_lst_flag_add_back(flags, ft_lst_flag_new('X', &xup_replace));
	ft_lst_flag_add_back(flags, ft_lst_flag_new('%', &pc_replace));
	if (!flags)
		return ((t_flag_list **)0);
	return (flags);
}
