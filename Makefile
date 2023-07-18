# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 14:41:13 by hyojocho          #+#    #+#              #
#    Updated: 2023/07/10 22:41:32 by choihyojong      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g
INC				= -I./headers -I./libft
NAME            = cub3d
RM              = rm -f
LIBS			= libft/libft.a

EXEC            = cub3d
SRCS_PATH	    = ./

MAIN_PATH  	    = ./
MAIN_SRCS       = main.c
MAIN            = $(addprefix $(MAIN_PATH), $(MAIN_SRCS))

PARSING_PATH  	= srcs/parsing/
PARSING_SRCS    = parsing.c args_validation.c getting_side_info.c initialize.c \
					line_validation.c map_validation.c linked_list.c \
					line_parse_utils.c making_map_array.c free_utils.c
PARSING         = $(addprefix $(PARSING_PATH), $(PARSING_SRCS))

ENGINE_PATH		= srcs/engine/
ENGINE			= $(wildcard srcs/engine/*.c)

SOURCES			= $(addprefix $(SRCS_PATH), $(MAIN))\
				  $(addprefix $(SRCS_PATH), $(PARSING))\
				  $(addprefix $(SRCS_PATH), $(ENGINE))

OBJECTS         = $(SOURCES:.c=.o)

#----------

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	MLX_DIR		:= ./mlx_mms_mac
	MLX_A		:= $(MLX_DIR)/libmlx.dylib
	MLX_FLAGS	:= -L$(MLX_DIR) -framework OpenGL -framework AppKit
else ifeq ($(UNAME), Linux)
	MLX_DIR		:= ./mlx_linux
	MLX_A		:= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	:= -L$(MLX_DIR) -lXext -lX11 -lm -lz
endif

INC += -I$(MLX_DIR) -I./headers/os_$(UNAME)
ENGINE			+= ./headers/os_$(UNAME)/os_$(UNAME)_mouse_func.c

#----------

all: $(NAME)

$(NAME): $(LIBS) $(MLX_A) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) $(MLX_A) $(MLX_FLAGS) -o $(EXEC)
	@echo "\n$(GREEN)$(EXEC) created!$(DEFAULT)\n"

$(LIBS) :
	@make -C libft all

$(MLX_A):
	@make --no-print-directory -C $(MLX_DIR)
ifeq ($(UNAME), Darwin)
	@install_name_tool -id $(MLX_A) $(MLX_A)
endif

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) $(OBJECTS)
	@$(RM) $(OBJECTS:.o=.d)
	make -C libft clean
	@cd $(MLX_DIR); make --no-print-directory clean

fclean: clean
	@$(RM) $(EXEC)
	@$(RM) $(LIBS)
	@cd $(MLX_DIR); make --no-print-directory clean
	@echo "\n$(BLUE)delete all!$(DEFAULT)\n"

re:
	@make fclean
	@make all

.PHONY: all clean fclean re

RED = \033[1;31m
PINK = \033[1;35m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
DEFAULT = \033[0m