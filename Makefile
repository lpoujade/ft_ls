# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/11 13:41:06 by lpoujade          #+#    #+#              #
#    Updated: 2016/02/11 17:14:57 by lpoujade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
CPPFLAGS=
CFLAGS=-Wall -Werror -Wextra
INCLUDEDIR=./includes
SRCDIR=./src
OBJDIR=./obj
CC=clang

SRCS= $(SRCDIR)/ft_ls.c $(SRCDIR)/lsdir.c

all: $(NAME)

$(NAME):
	$(CC) $(CLFAGS) -o $(NAME) $(SRCS) -I$(INCLUDEDIR)

