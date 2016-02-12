# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/11 13:41:06 by lpoujade          #+#    #+#              #
#    Updated: 2016/02/12 16:05:52 by lpoujade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
CPPFLAGS=-Iincludes/
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=-Llibft/
LDLIBS=-lft
SRCDIR=./src
OBJDIR=./obj
CC=clang

SRCS= ft_ls.c lsdir.c paramss.c
OBJS=$(SRCS:.c=.o)

OBJS:= $(addprefix $(OBJDIR)/,$(OBJS))
SRCS:= $(addprefix $(SRCDIR)/,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJS): $(SRCS) $(LIB)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -Ilibft/includes/ -o $@ -c $<

$(LIB):
	-make -C $(LIB)

clean:
	-rm -r $(OBJDIR)
	make -C libft/ clean

fclean: clean
	-rm $(NAME)
	-rm libft/libft.a

re: fclean $(NAME)
