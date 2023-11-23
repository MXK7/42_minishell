# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 10:23:14 by mpoussie          #+#    #+#              #
#    Updated: 2023/11/23 10:24:02 by mpoussie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

SRCS =	TODO

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./include/libft
MLX_DIR = ./include/minilibx

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx_Linux.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LIBFT) $(MLX) -g3 -lXext -lX11 -lm -fsanitize=address -lz -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re