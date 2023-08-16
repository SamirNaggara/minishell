/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:42:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/05/30 11:13:31 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100 
# endif

# ifndef NB_FILE_MAX
#  define NB_FILE_MAX 100
# endif

char	*get_next_line(int fd);
int		ft_read(char **line, int fd);
char	*ft_strjoin_custom(char *reading, char *tmp);
size_t	ft_strlen_custom(const char *str);
int		ft_strchr_custom(const char *s, int c);
size_t	ft_strlcpy_custom(char *dest, char *src, size_t size);
char	*ft_strdup_custom(char *s);

#endif
