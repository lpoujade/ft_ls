# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/11 13:41:06 by lpoujade          #+#    #+#              #
#    Updated: 2016/02/12 21:40:36 by lpoujade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
SRCDIR=./src
OBJDIR=./.obj

CC=clang
CFLAGS=-Wall -Werror -Wextra -g
CPPFLAGS=-Iincludes/ -Ilibft/includes

LDFLAGS=-Llibft/
LDLIBS=-lft

LIB=libft/libft.a

SRC=ft_ls.c paramss.c lsdir.c
OBJ=$(SRC:.c=.o)

SRCS=$(addprefix $(SRCDIR)/,$(SRC))
OBJS=$(addprefix $(OBJDIR)/,$(OBJ))

all: $(NAME) $(LIB)

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "linking to" $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "compiling" $@

$(LIB):
	-make -C libft/

clean:
	-rm $(OBJS)

fclean: clean
	-rm $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
