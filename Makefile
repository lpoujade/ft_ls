# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/11 13:41:06 by lpoujade          #+#    #+#              #
#    Updated: 2016/06/02 14:50:01 by lpoujade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
SRCDIR=./src
OBJDIR=./.obj

CC=clang
CFLAGS=-Wall -Werror -Wextra -g -Wno-unicode-whitespace
CPPFLAGS=-Iincludes/ -Ilibft/includes

LDFLAGS=-Llibft/
LDLIBS=-lft

LIB=libft/libft.a

SRC=ft_ls.c lsfile.c lists.c loadinfo.c params.c output.c utils.c
OBJ=$(SRC:.c=.o)

SRCS=$(addprefix $(SRCDIR)/,$(SRC))
OBJS=$(addprefix $(OBJDIR)/,$(OBJ))

# GCOV, llvm specific
# CFLAGS+=-g -fprofile-arcs -ftest-coverage
# LDFLAGS+=--coverage


all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@echo "linking to\033[32m" $@ "\033[0m ... "
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p .obj
	@echo "compiling\033[36m" $@ "\033[0m ..."
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIB):
	make -C libft/

clean:
	-@rm $(OBJS) && echo "deleting" $(OBJS)

covclean:
	-@rm $(OBJS:.o=.gcno) && echo "deleting" $(OBJS:.o=.gcno)
	-@rm $(OBJS:.o=.gcda) && echo "deleting" $(OBJS:.o=.gcda)

fclean: clean
	-@rm $(NAME) && echo "deleting" $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

