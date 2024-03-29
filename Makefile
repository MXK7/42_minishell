# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 10:23:14 by mpoussie          #+#    #+#              #
#    Updated: 2024/02/07 05:56:21 by mpoussie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
INCLUDES    = includes/
SRC_DIR     = src/
OBJ_DIR     = obj/

LIBFT_DIR   = $(INCLUDES)src/libft/
LIBFT       = $(LIBFT_DIR)libft.a

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g -O0
PRFLAGS     = -lreadline
RM          = rm -rf

LEXING_DIR  = lexing/
LEXING      = tokenize_handler tokenize_utils t_lexer_utils quotes_handler

PARSING_DIR = parsing/
PARSING     = parser parser_utils redirection_handler t_command_utils

EXPDING_DIR = expanding/
EXPDING     = expander expander_utils

EXE_DIR     = executing/
EXE         = handler_exe execute redirection heredoc

BUILTIN_DIR = builtin/
BUILTIN     = handler_builtin utils_builtin env echo pwd exit cd unset

_EXPORT_DIR = $(BUILTIN_DIR)export/
_EXPORT     = export print_env_sorted export_multiple_env

_ENV_DIR 	= $(BUILTIN_DIR)env/
_ENV     	= add_env edit_env get_env is_exist_env update_env remove_env

SIGNAL_DIR  = signal/
SIGNAL      = signal

SRC_FILES  += main utils t_global_utils error
SRC_FILES  += $(addprefix $(LEXING_DIR), $(LEXING))
SRC_FILES  += $(addprefix $(PARSING_DIR), $(PARSING))
SRC_FILES  += $(addprefix $(EXPDING_DIR), $(EXPDING))
SRC_FILES  += $(addprefix $(BUILTIN_DIR), $(BUILTIN))
SRC_FILES  += $(addprefix $(_EXPORT_DIR), $(_EXPORT))
SRC_FILES  += $(addprefix $(_ENV_DIR), $(_ENV))
SRC_FILES  += $(addprefix $(SIGNAL_DIR), $(SIGNAL))
SRC_FILES  += $(addprefix $(EXE_DIR), $(EXE))

SRC         = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJ_CACHE   = .cache_exists

###

all: 			$(LIBFT) $(NAME)

$(LIBFT):
					@make -C $(LIBFT_DIR)

$(NAME): 		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(PRFLAGS) $(LIBFT) -o $(NAME)
					@echo "\033[0;32m$(shell echo $(NAME) | tr '[:lower:]' '[:upper:]') : COMPILED\033[0m"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_CACHE)
					@echo "Compiling $<"
					@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJ_CACHE):
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(LEXING_DIR)
					@mkdir -p $(OBJ_DIR)$(PARSING_DIR)
					@mkdir -p $(OBJ_DIR)$(EXPDING_DIR)
					@mkdir -p $(OBJ_DIR)$(BUILTIN_DIR)
					@mkdir -p $(OBJ_DIR)$(_EXPORT_DIR)
					@mkdir -p $(OBJ_DIR)$(_ENV_DIR)
					@mkdir -p $(OBJ_DIR)$(SIGNAL_DIR)
					@mkdir -p $(OBJ_DIR)$(EXE_DIR)

clean:
					@make clean -C $(LIBFT_DIR)
					$(RM) $(OBJ_DIR)
					$(RM) $(OBJ_CACHE)
					@echo "minishell and libs object files cleaned!"

fclean: 		clean
					@make fclean -C $(LIBFT_DIR)
					$(RM) $(NAME)
					@echo "minishell and libs executable files cleaned!"

re: 			fclean all
					@echo "Cleaned and rebuilt everything for minishell!"

.PHONY:			all clean fclean re

.SILENT:
