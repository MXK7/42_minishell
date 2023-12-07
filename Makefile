# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 10:23:14 by mpoussie          #+#    #+#              #
#    Updated: 2023/12/07 18:41:23 by mpoussie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g -I ./includes/
PRFLAGS = -lreadline

SRCS = src/main.c \
	   src/utils.c \
	   src/handler_builtin.c \
	   src/handler_parsing.c \
	   src/handler_signal.c

SRCS += src/builtin/env.c \
		src/builtin/others.c \
		src/builtin/echo.c \
		src/builtin/pwd.c \

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./includes/src/libft
LIBFT = $(LIBFT_DIR)/libft.a

GCLIB_DIR = ./includes/src/gc/
GCLIB = $(GCLIB_DIR)/libgc.a

all: $(NAME)
	@echo "\033[0;32m$(shell echo $(NAME) | tr '[:lower:]' '[:upper:]') : COMPILED\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(GCLIB_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(PRFLAGS) $(LIBFT) $(GCLIB)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(GCLIB_DIR)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(GCLIB_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: