# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 10:23:14 by mpoussie          #+#    #+#              #
#    Updated: 2023/12/06 18:49:14 by arazzok          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
INCLUDES    = includes/
SRC_DIR     = src/
OBJ_DIR     = obj/

LIBFT_DIR   = $(INCLUDES)src/libft/
LIBFT       = $(LIBFT_DIR)libft.a

GCLIB_DIR   = $(INCLUDES)src/gc/
GCLIB       = $(GCLIB_DIR)libgc.a

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g -I $(INCLUDES)
PRFLAGS     = -lreadline
RM          = rm -rf

PARSING_DIR = parsing/
PARSING     = handler_parsing

BUILTIN_DIR = builtin/
BUILTIN     = handler_builtin env

SIGNAL_DIR = signal/
SIGNAL     = handler_signal signal

SRC_FILES  += main
SRC_FILES  += $(addprefix $(PARSING_DIR), $(PARSING))
SRC_FILES  += $(addprefix $(BUILTIN_DIR), $(BUILTIN))
SRC_FILES  += $(addprefix $(SIGNAL_DIR), $(SIGNAL))

SRC         = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJ_CACHE   = .cache_exists

###

all: 			$(LIBFT) $(GCLIB) $(NAME)

$(LIBFT):
					@make -C $(LIBFT_DIR)

$(GCLIB):
					@make -C $(GCLIB_DIR)

$(NAME): 		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(PRFLAGS) $(LIBFT) $(GCLIB) -o $(NAME)
					@echo "\033[0;32m$(shell echo $(NAME) | tr '[:lower:]' '[:upper:]') : COMPILED\033[0m"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_CACHE)
					@echo "Compiling $<"
					@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJ_CACHE):
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(PARSING_DIR)
					@mkdir -p $(OBJ_DIR)$(BUILTIN_DIR)
					@mkdir -p $(OBJ_DIR)$(SIGNAL_DIR)

clean:
					@make clean -C $(LIBFT_DIR)
					@make clean -C $(GCLIB_DIR)
					$(RM) $(OBJ_DIR)
					$(RM) $(OBJ_CACHE)
					@echo "minishell and libs object files cleaned!"

fclean: 		clean
					@make fclean -C $(LIBFT_DIR)
					@make fclean -C $(GCLIB_DIR)
					$(RM) $(NAME)
					@echo "minishell and libs executable files cleaned!"

re: 			fclean all
					@echo "Cleaned and rebuilt everything for minishell!"

.PHONY:			all clean fclean re

.SILENT: