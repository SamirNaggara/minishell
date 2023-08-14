NAME		= 	minishell
FLAGS		= 	-Wall -Wextra -Werror
DEBUG_FLAGS =	
RM			= 	rm -f
GREEN		= 	\033[0;32m
BIG		= 	\033[0;1m
RESET		= 	\033[0m
CC	=	gcc $(FLAGS)
RM	=	rm -f
LOG = log.txt	



SOURCES	=	./*.c \
			./parser/*.c \
			./lexer/*.c \
			./executor/*.c



OBJETS	=	$(SOURCES:.c=.o)			


all		: $(NAME)
	@echo "$(GREEN)\nCompilation $(NAME) over\n$(RESET)"
	@echo "$(BIG)Il suffit maintenant de compiler ./$(NAME)$(RESET)"

$(NAME): $(OBJETS)
	@echo "Création de l'executable $(NAME)"
	@$(CC) $(FLAGS) -o $@ $^

%.o: %.c
	@echo "Génération de $@"
	@$(CC) $(FLAGS) -o $@ -c $< 



clean	:
	@echo "Suppression des .o de $(NAME)"
	@$(RM) $(OBJETS)
	@echo "\n$(GREEN)Tout les .o ont bien été effacé$(RESET)"


fclean	:	clean
	@echo "Suppression de $(NAME)"
	@$(RM) $(NAME)
	@echo "Suppression de a.out au cas ou"
	@$(RM) a.out
	@echo "\n$(GREEN)Tout les fichiers ont bien été effacés$(RESET)\n"

re		:	fclean all

.PHONY: all clean fclean re
