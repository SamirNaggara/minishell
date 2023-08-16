NAME	=	libftprintf.a
LIBS	=	srcs/libft.a
FLAGS	= -Wall -Wextra -Werror		


SOURCES	=	./ft_printf.c \
				./ft_main/ft_first_flag.c \
				./ft_main/ft_init_flag.c \
				./ft_main/ft_modify_str.c \
				./ft_libft_add/ft_itoa_hexa.c \
				./ft_libft_add/ft_itoa_hexa_ulong.c \
				./ft_libft_add/ft_itoa_unsigned_long.c \
				./ft_libft_add/ft_putstr.c \
				./ft_libft_add/ft_strtoupper.c \
				./ft_list_helper/ft_lst_flag_add_back.c \
				./ft_list_helper/ft_lst_flag_new.c \
				./ft_list_helper/ft_lstflag_clear.c\
				./ft_list_helper/ft_init_infos.c\
				./ft_replace/c_replace.c\
				./ft_replace/d_replace.c\
				./ft_replace/i_replace.c\
				./ft_replace/p_replace.c\
				./ft_replace/pc_replace.c\
				./ft_replace/s_replace.c\
				./ft_replace/u_replace.c\
				./ft_replace/x_replace.c\
				./ft_replace/X_replace.c
 

INC		=	includes/

OBJETS	=	$(SOURCES:.c=.o)			

CC	=	gcc $(FLAGS) -I $(INC)
RM	=	rm -f				

$(NAME)	:	$(OBJETS)
			make -C libft
			cp libft/libft.a .
			mv libft.a $(NAME)
			ar rc $(NAME) $(OBJETS) 



clean	:
		$(RM) $(OBJETS)
		make clean -C libft				
		$(CLEAN)				 

fclean	:	clean	
		$(RM) libft/libft.a			
		$(RM) $(NAME)		

re		:	fclean all

all		:$(NAME)