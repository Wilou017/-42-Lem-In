# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 12:19:31 by amaitre           #+#    #+#              #
#    Updated: 2016/09/19 19:33:57 by amaitre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in

SRC			=	src/main.c
SRC			+=	src/init.c
SRC			+=	src/list.c
SRC			+=	src/pushback.c
SRC			+=	src/paths.c
SRC			+=	src/search.c
SRC			+=	src/crossing.c
SRC			+=	src/already_exist.c
SRC			+=	src/free_all.c

SRCO		=	$(SRC:.c=.o)
HEADERSLIB	=	libftprintf/includes
HEADERS		=	includes
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

all: $(NAME)

re: fclean all

%.o: %.c
	@echo "\033[32mLem-In  :\033[0m [Compilation:\033[33m $@\033[0m]"
	@$(CC) -o $@ -c $< $(CFLAGS) -I $(HEADERSLIB) -I $(HEADERS)

$(NAME): $(SRCO)
	@make -C libftprintf/
	@$(CC)  $(CFLAGS) -o $@ $^ libftprintf/libftprintf.a
	@echo "[\033[32m--------------------------\033[0m]"
	@echo "[\033[36m------ OK - Lem-In -------\033[0m]"
	@echo "[\033[32m--------------------------\033[0m]"
	@echo "\033[32muse: ./$(NAME)\033[0m"

clean:
	@echo "\033[32mLem-In  :\033[0m [\033[31mSuppression des .o\033[0m]"
	@make clean -C libftprintf/
	@rm -f $(SRCO)

fclean:
	@echo "\033[32mLem-In  :\033[0m [\033[31mSuppression des .o\033[0m]"
	@rm -f $(SRCO)
	@echo "\033[32mLem-In  :\033[0m [\033[31mSuppression de $(NAME)\033[0m]"
	@make fclean -C libftprintf/
	@rm -f $(NAME)

.PHONY: re clean fclean all
