/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:59:53 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/11 07:56:11 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	t_flag_list	**flag_list;
	va_list		args;
	char		*to_return;
	t_infos		*infos;
	size_t		retour;

	infos = ft_init_infos();
	if (!infos)
		return (0);
	va_start(args, str);
	flag_list = create_flag_list();
	if (!flag_list)
		return (free_infos(infos));
	*(infos->size) = ft_strlen(str);
	to_return = ft_modify_str(flag_list, str, &args, infos);
	if (!to_return)
		return (free_struct(flag_list, infos));
	retour = *(infos->size);
	ft_putstr(to_return, infos->size, FD_TO_WRITE);
	ft_lstflag_clear(flag_list, free);
	free(to_return);
	free_infos(infos);
	va_end(args);
	return ((int)retour);
}

int	fd_printf(int fd, const char *str, ...)
{
	t_flag_list	**flag_list;
	va_list		args;
	char		*to_return;
	t_infos		*infos;
	size_t		retour;

	infos = ft_init_infos();
	if (!infos)
		return (0);
	va_start(args, str);
	flag_list = create_flag_list();
	if (!flag_list)
		return (free_infos(infos));
	*(infos->size) = ft_strlen(str);
	to_return = ft_modify_str(flag_list, str, &args, infos);
	if (!to_return)
		return (free_struct(flag_list, infos));
	retour = *(infos->size);
	ft_putstr(to_return, infos->size, fd);
	ft_lstflag_clear(flag_list, free);
	free(to_return);
	free_infos(infos);
	va_end(args);
	return ((int)retour);
}

/*
int	main(){


	//ft_printf("bah%ca\nb", 0);
	//char	*ptr;
	//unsigned int i = 14748364955 ;
	//long long j = -9223372036854775807;
	//j--;
	//int nb1 = ft_printf("a%sa\n", ptr);
	int nb1 = ft_printf(" %c%c\n", '\0', '1');
	int nb2 = printf(" %c%c\n", '\0', '1');
	printf("Mon printf: %d\nLe vrai printf :  %d\n", nb1, nb2);

	// char *chaine;
	// size_t	*size;

	// size = malloc(sizeof(chaine));
	// *size = 10;
	// chaine = ft_strdup("cha%%%%%ine");
	// ;
	// printf("%s\n", handle_percent(chaine, size));

	//ft_printf("Salut ça \0va ?");
	// printf("%s\n",chaine);
	//printf(" %c ", '0');
	//printf("a%s", "");
	//printf("%s\n", ft_itoa_hexa(140723940386924));
	//nbr = 8;
	//ptr = &nbr;
	//printf("Voila un pointeur, enfin je crois : %p\n", ptr);
	//ft_printf("Test 1 : ok c'est la chaine simple\n\n");
	//printf("Test 1 : % ok c'est la chaine simple\n\n");
	// ft_printf("Test 2 : La y'a un int : %d\n\n", -25);
	// ft_printf("Test 3 : La y'a une chaine : %s\n\n", "La chaine");
	// ft_printf("Test 4 : La y'a une chaine : 
	//%s et la le nombre\n\n", "La chaine");
	// ft_printf("Test 4 : La y'a une chaine : 
	//%s et la le nombre\n\n", "La chaine");
	// ft_printf("Test 5 : La y'a un seul char : %c\n\n", 'r');
	// ft_printf("Test 6 : Voila le pointeur%papres\n\n", ptr);
	//printf("Test 6 : Voila le pointeur%papres\n", ptr);
	//ft_printf("Test 7 : Voici le i qui affiche un nombre i: %i\n\n", 123);
	//ft_printf("Test 8 : La y'a un int : %u\n\n", -3);
	//printf("Test 8 : La y'a un int : %u\n\n", -3);
	//ft_printf("Test 9 : La y'a un nombre hexa : %x\n\n", 421);
	//printf("Test 9 : La y'a un nombre hexa : %x\n\n", 421);
	//ft_printf("Test 10 : La y'a un nombre hexa maj: %X\n\n", 421);
	//ft_printf("Test 11 : La y'a un pourcentage : %%aa\n\n");
	//printf("%d\n", ft_atoi(av[1]));
	//printf("voila");
	return (0);
}
*/