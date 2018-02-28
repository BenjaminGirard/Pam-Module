SCRIPT_FLAGS	=	scripts

SRC		=	cmd_handler.c		\
			container_handler.c	\
			file_handler.c		\
			logger.c		\
			pamela.c		\
			pam_user_tools.c	\
			paths_maker.c		\
			strtools.c

OBJS		=	$(SRC:.c=.o)

NAME		=	pam_lib.so

CFLAGS		+=	-fpic -W -Wall -Wextra

LDFLAGS		+=	 -shared

RM		=	rm -f

CC		=	gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

check:
	$(SCRIPT_FLAGS)/check.sh

install:
	$(SCRIPT_FLAGS)/install.sh $(NAME)

uninstall:
	sudo $(SCRIPT_FLAGS)/uninstall.sh $(NAME)

test:

.PHONY: all clean fclean re
