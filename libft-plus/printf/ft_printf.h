/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:43:10 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/14 15:02:11 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <string.h>

# ifndef FD_TO_WRITE
#  define FD_TO_WRITE 1
# endif

typedef struct s_infos
{
	size_t				*size;
	size_t				*prev;
}t_infos;
typedef struct s_flag_list
{
	char				type;
	size_t				length_flag;
	char				*(*func_replace)(char*, struct s_flag_list*,
			va_list*, t_infos *infos);
	struct s_flag_list	*next;
}t_flag_list;

int					ft_printf(const char *str, ...);
int					fd_printf(int fd, const char *str, ...);
t_flag_list			**create_flag_list(void);
t_flag_list			*ft_lst_flag_new(int type, char *(*func_replace)
						(char*, struct s_flag_list*, va_list*, t_infos*));
t_flag_list			*first_flag(t_flag_list **flag_list, const char *str,
						size_t *size, size_t *prev);
char				*ft_modify_str(t_flag_list **flag_list, const char *str,
						va_list *args,
						t_infos *infos);
void				ft_lst_flag_add_back(t_flag_list **lst, t_flag_list *new);
void				ft_lstflag_clear(t_flag_list **lst, void (*del)(void *));
char				*replace_flag_by_str(char *str, t_flag_list *flag,
						char *arg_str, size_t *size);
char				*s_replace(char *str, t_flag_list *flag, va_list *args,
						t_infos *infos);
char				*d_replace(char *str, t_flag_list *flag, va_list *args,
						t_infos *infos);
char				*i_replace(char *str, t_flag_list *flag, va_list *args,
						t_infos *infos);
char				*c_replace(char *str, t_flag_list *flag, va_list *args,
						t_infos *infos);
char				*p_replace(char *str, t_flag_list *flag, va_list *args,
						t_infos *infos);
char				*u_replace(char *str, t_flag_list *flag, va_list *args,
						t_infos *infos);
char				*x_replace(char *str, t_flag_list *flag, va_list *args,
						t_infos *infos);
char				*xup_replace(char *str, t_flag_list *flag, va_list *args,
						t_infos *infos);
char				*pc_replace(char *str, t_flag_list *flag, va_list *args,
						t_infos *infos);
void				ft_putstr(char *str, size_t *size, int fd);
char				*ft_itoa_long(unsigned int n);
char				*ft_itoa_hexa(unsigned long n);
char				*ft_itoa_hexa_ulong(long long n);
void				del(void *content);
void				ft_strtoupper(char *str);
char				*remove_one_char(char *str, size_t pos, size_t *size);
char				*str_search_percent(const char *str, size_t *size,
						size_t *prev);
t_infos				*ft_init_infos(void);
int					free_infos(t_infos *infos);
int					free_struct(t_flag_list **flag_list, t_infos *infos);
void				ft_increment(t_infos *infos);
char				*free_nbr_to_display(char *char_nbr, char *char_to_display);
long long			ft_get_len4(long long n);
char				*ft_initialise_result4(long long len);
long long			ft_power4(long long nb, long long power);
size_t				ft_get_len3(unsigned long n);
char				*ft_initialise_result3(size_t len);
long				ft_power3(unsigned long nb, long power);
unsigned long long	ft_get_len_lg(unsigned long long n);
char				*ft_initialise_result_lg(unsigned long long len);
unsigned long long	ft_power5(unsigned long long nb, unsigned long long power);

// char		*handle_percent(char *str, size_t *size);

#endif