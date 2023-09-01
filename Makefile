NAME		= 	minishell
LIB_PATH	= 	libft-plus
LIBFT 		= 	$(LIB_PATH)/libft.a
PRINTF		=	$(LIB_PATH)/printf.a 
GNL			=	$(LIB_PATH)/gnl.a 
FLAGS		= 	-Wall -Wextra -Werror 
RM			= 	rm -f
GREEN		= 	\033[0;32m
BIG		= 	\033[0;1m
RESET		= 	\033[0m
CC	=	cc $(FLAGS)
RM	=	rm -f				


SOURCES	=	./main.c \
			./executor/executor.c \
			./executor/fill_cmd.c \
			./executor/process.c \
			./executor/pipe.c \
			./executor/exec.c \
			./executor/redirections.c \
			./executor/child.c \
			./executor/child2.c \
			./executor/free_struct.c \
			./executor/here_doc.c \
			./executor/exec_one_cmd.c \
			./executor/fill_redirection.c \
			./executor/dup2.c \
			./utils/add_slash.c \
			./utils/ft_utils.c \
			./lexer/lexer.c \
			./lexer/quotes.c \
			./lexer/operator.c \
			./lexer/space.c \
			./lexer/delimiter.c \
			./lexer/fill_operator.c \
			./parser/parser.c \
			./parser/redir_in_cmd.c \
			./parser/redir_in_cmd2.c \
			./parser/simple_cmd.c \
			./parser/syntaxe_error.c \
			./parser/utils.c \
			./parser/built_in.c \
			./parser/parse_args.c \
			./parser/parse_cmds.c \

OBJETS	=	$(SOURCES:.c=.o)			


all		: lib $(NAME)
	@echo "$(GREEN)\nBravo le projet est compilé.$(RESET)\n\n$(RESET)"


$(NAME): $(OBJETS)
	@echo "Création de l'executable $(NAME)"
	@$(CC) -o $@ $^ -lreadline $(PRINTF) $(LIBFT) $(GNL)

%.o: %.c
	@echo "Génération de $@"
	@$(CC) -o $@ -c $< 

lib	: 
	@echo "Je déclenche le Makefile de Libft-plus\n"
	@$(MAKE) --no-print-directory -C $(LIB_PATH) all
	@echo "Je sors du Makefile de Libft-plus"


clean	:
	@$(RM) $(OBJETS)


fclean	:	clean
	@echo "Suppression de $(NAME)"
	@$(RM) $(NAME)
	@echo "Suppression de a.out au cas ou"
	@$(RM) a.out
	@echo "Je rentre dans la librairie libft-plus"
	@$(MAKE) --no-print-directory -C $(LIB_PATH) fclean
	@echo "Je sors de la librairie libft-plus"
	@echo "\n$(GREEN)Tout les fichiers ont bien été effacés$(RESET)\n"
	@echo "Suppression de tout les fichiers ajoutés par l'utilisateur\n"


re		:	fclean all

.PHONY: all clean fclean re lib





