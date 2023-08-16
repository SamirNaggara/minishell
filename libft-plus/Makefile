NAME		= libft-plus
LIBFT		= libft.a
LIBFT_PATH	= libft
PRINTF		= printf.a
PRINTF_PATH	= printf
GNL			= gnl.a
GNL_PATH	= get-next-line
FLAGS		= -Wall -Wextra -Werror -g	
RM			= rm -f
GREEN		= \033[0;32m
BIG			= \033[0;1m
RESET		= \033[0m

SOURCES_LIBFT = 	./$(LIBFT_PATH)/ft_atoi.c \
	./$(LIBFT_PATH)/ft_bzero.c \
	./$(LIBFT_PATH)/ft_calloc.c \
	./$(LIBFT_PATH)/ft_isalpha.c \
	./$(LIBFT_PATH)/ft_isalnum.c \
	./$(LIBFT_PATH)/ft_isascii.c \
	./$(LIBFT_PATH)/ft_isdigit.c \
	./$(LIBFT_PATH)/ft_isprint.c \
	./$(LIBFT_PATH)/ft_itoa.c \
	./$(LIBFT_PATH)/ft_memchr.c \
	./$(LIBFT_PATH)/ft_memcmp.c \
	./$(LIBFT_PATH)/ft_memcpy.c \
	./$(LIBFT_PATH)/ft_memmove.c \
	./$(LIBFT_PATH)/ft_memset.c \
	./$(LIBFT_PATH)/ft_putchar_fd.c \
	./$(LIBFT_PATH)/ft_putendl_fd.c \
	./$(LIBFT_PATH)/ft_putnbr_fd.c \
	./$(LIBFT_PATH)/ft_putstr_fd.c \
	./$(LIBFT_PATH)/ft_split.c \
	./$(LIBFT_PATH)/ft_strchr.c \
	./$(LIBFT_PATH)/ft_strdup.c \
	./$(LIBFT_PATH)/ft_striteri.c \
	./$(LIBFT_PATH)/ft_strjoin.c \
	./$(LIBFT_PATH)/ft_strlcat.c \
	./$(LIBFT_PATH)/ft_strlcpy.c \
	./$(LIBFT_PATH)/ft_strlen.c \
	./$(LIBFT_PATH)/ft_strmapi.c \
	./$(LIBFT_PATH)/ft_strncmp.c \
	./$(LIBFT_PATH)/ft_strnstr.c \
	./$(LIBFT_PATH)/ft_strrchr.c \
	./$(LIBFT_PATH)/ft_strtrim.c \
	./$(LIBFT_PATH)/ft_substr.c \
	./$(LIBFT_PATH)/ft_tolower.c \
	./$(LIBFT_PATH)/ft_toupper.c \
	./$(LIBFT_PATH)/ft_lstadd_back.c \
	./$(LIBFT_PATH)/ft_lstadd_front.c \
	./$(LIBFT_PATH)/ft_lstclear.c \
	./$(LIBFT_PATH)/ft_lstdelone.c \
	./$(LIBFT_PATH)/ft_lstiter.c \
	./$(LIBFT_PATH)/ft_lstlast.c \
	./$(LIBFT_PATH)/ft_lstmap.c \
	./$(LIBFT_PATH)/ft_lstnew.c \
	./$(LIBFT_PATH)/ft_lstsize.c

SOURCES_PRINTF	=	./$(PRINTF_PATH)/ft_printf.c \
	./$(PRINTF_PATH)/ft_main/ft_first_flag.c \
	./$(PRINTF_PATH)/ft_main/ft_init_flag.c \
	./$(PRINTF_PATH)/ft_main/ft_modify_str.c \
	./$(PRINTF_PATH)/ft_libft_add/ft_itoa_hexa.c \
	./$(PRINTF_PATH)/ft_libft_add/ft_itoa_hexa_ulong.c \
	./$(PRINTF_PATH)/ft_libft_add/ft_itoa_unsigned_long.c \
	./$(PRINTF_PATH)/ft_libft_add/ft_putstr.c \
	./$(PRINTF_PATH)/ft_libft_add/ft_strtoupper.c \
	./$(PRINTF_PATH)/ft_list_helper/ft_lst_flag_add_back.c \
	./$(PRINTF_PATH)/ft_list_helper/ft_lst_flag_new.c \
	./$(PRINTF_PATH)/ft_list_helper/ft_lstflag_clear.c\
	./$(PRINTF_PATH)/ft_list_helper/ft_init_infos.c\
	./$(PRINTF_PATH)/ft_replace/c_replace.c\
	./$(PRINTF_PATH)/ft_replace/d_replace.c\
	./$(PRINTF_PATH)/ft_replace/i_replace.c\
	./$(PRINTF_PATH)/ft_replace/p_replace.c\
	./$(PRINTF_PATH)/ft_replace/pc_replace.c\
	./$(PRINTF_PATH)/ft_replace/s_replace.c\
	./$(PRINTF_PATH)/ft_replace/u_replace.c\
	./$(PRINTF_PATH)/ft_replace/x_replace.c\
	./$(PRINTF_PATH)/ft_replace/X_replace.c

SOURCES_GNL	=	./$(GNL_PATH)/get_next_line.c \
	./$(GNL_PATH)/get_next_line_utils.c \

OBJETS_LIBFT = $(SOURCES_LIBFT:.c=.o)
OBJETS_PRINTF = $(SOURCES_PRINTF:.c=.o)
OBJETS_GNL = $(SOURCES_GNL:.c=.o)

all: progress $(LIBFT) $(PRINTF) $(GNL)
	@echo "\n$(BIG)	Bravo, les librairies $(LIBFT) $(PRINTF) $(GNL) sont disponibles dans $(NAME)$(RESET)\n"

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $<

$(LIBFT): $(OBJETS_LIBFT)
	@echo "	Création de la librairie $(LIBFT)"
	@ar rcs $(LIBFT) $(OBJETS_LIBFT)

$(PRINTF): $(OBJETS_PRINTF)
	@echo "	Création de la librairie $(PRINTF)"
	@ar rcs $(PRINTF) $(OBJETS_PRINTF)

$(GNL): $(OBJETS_GNL)
	@echo "	Création de la librairie $(GNL)"
	@ar rcs $(GNL) $(OBJETS_GNL)



clean:
	@echo "	Suppresion des .o de LIBFT"
	@rm -f $(OBJETS_LIBFT)
	@echo "	Suppresion des .o de PRINTF"
	@rm -f $(OBJETS_PRINTF)
	@echo "	Suppresion des .o de GNL"
	@rm -f $(OBJETS_GNL)
fclean:clean
	@echo "	Suppresion de la librairie $(LIBFT)"
	@rm -f $(LIBFT)
	@echo "	Suppresion de la librairie $(PRINTF)"
	@rm -f $(PRINTF)
	@echo "	Suppresion de la librairie $(GNL)"
	@rm -f $(GNL)

re: fclean all

.PHONY: all clean fclean re libft printf gnl progress