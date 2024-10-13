# Nom de l'exécutable
NAME = sokoban

# Fichiers sources
SRCS = main.c

all: $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean re
