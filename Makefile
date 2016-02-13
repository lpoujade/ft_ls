# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/11 13:41:06 by lpoujade          #+#    #+#              #
#    Updated: 2016/02/13 18:28:59 by lpoujade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
SRCDIR=./src
OBJDIR=./.obj

CC=clang
CFLAGS=-Wall -Werror -Wextra
CPPFLAGS=-Iincludes/

LDFLAGS=-Llibft/
LDLIBS=-lft

LIB=libft/libft.a

SRC=ft_ls.c paramss.c lsdir.c lists.c
OBJ=$(SRC:.c=.o)

SRCS=$(addprefix $(SRCDIR)/,$(SRC))
OBJS=$(addprefix $(OBJDIR)/,$(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS) && echo -e "linking to\033[32m" $@ "\033[0m("`stat -c "%s" $@` "bytes)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ && echo -e "compiling\033[36m" $@ "\033[0m("`stat -c "%s" $@` "bytes)"

$(LIB):
	make -C libft/

clean:
	-@rm $(OBJS) && echo -e "deleting" $(OBJS)

fclean: clean
	-@rm $(NAME) && echo -e "deleting" $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
