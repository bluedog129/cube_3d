# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 14:41:13 by hyojocho          #+#    #+#              #
#    Updated: 2023/07/18 14:19:04 by hyojocho         ###   ########.fr        #
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

MAIN_PATH  	    = ./srcs/
MAIN_SRCS       = main.c
MAIN            = $(addprefix $(MAIN_PATH), $(MAIN_SRCS))
BONUS_MAIN_PATH  	    = ./srcs_bonus/
BONUS_MAIN_SRCS       = main_bonus.c
BONUS_MAIN            = $(addprefix $(BONUS_MAIN_PATH), $(BONUS_MAIN_SRCS))

PARSING_PATH  	= srcs/parsing/
PARSING_SRCS    = parsing.c args_validation.c getting_side_info.c initialize.c \
					line_validation.c map_validation.c linked_list.c \
					line_parse_utils.c making_map_array.c free_utils.c
PARSING         = $(addprefix $(PARSING_PATH), $(PARSING_SRCS))
BONUS_PARSING_PATH  	= srcs_bonus/parsing/
BONUS_PARSING_SRCS    = parsing_bonus.c args_validation_bonus.c getting_side_info_bonus.c initialize_bonus.c \
						line_validation_bonus.c map_validation_bonus.c linked_list_bonus.c \
						line_parse_utils_bonus.c making_map_array_bonus.c free_utils_bonus.c
BONUS_PARSING         = $(addprefix $(BONUS_PARSING_PATH), $(BONUS_PARSING_SRCS))

ENGINE_PATH		= srcs/engine/
ENGINE_SRCS		= draw_utils1.c   draw_utils2.c   engine_main.c   etc_utils.c     hook_utils.c    init_utils1.c   input_event.c
ENGINE			= $(addprefix $(ENGINE_PATH), $(ENGINE_SRCS))
BONUS_ENGINE_PATH		= srcs_bonus/engine/
BONUS_ENGINE_SRCS		= door_event_utils_bonus.c draw_hdoor_utils_bonus.c draw_utils1_bonus.c draw_utils3_bonus.c engine_main_bonus.c hook_utils_bonus.c input_event_bonus.c \
						  door_list_utils1_bonus.c draw_minimap_utils_bonus.c draw_utils2_bonus.c draw_vdoor_utils_bonus.c etc_utils_bonus.c init_utils1_bonus.c
BONUS_ENGINE			= $(addprefix $(BONUS_ENGINE_PATH), $(BONUS_ENGINE_SRCS))

SOURCES			= $(addprefix $(SRCS_PATH), $(MAIN))\
				  $(addprefix $(SRCS_PATH), $(PARSING))\
				  $(addprefix $(SRCS_PATH), $(ENGINE))

BONUS_SOURCES			= $(addprefix $(SRCS_PATH), $(BONUS_MAIN))\
						  $(addprefix $(SRCS_PATH), $(BONUS_PARSING))\
						  $(addprefix $(SRCS_PATH), $(BONUS_ENGINE))

OBJECTS         = $(SOURCES:.c=.o)

BONUS_OBJECTS   = $(BONUS_SOURCES:.c=.o)

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
BONUS_ENGINE	+= ./headers/os_$(UNAME)/os_$(UNAME)_mouse_func_bonus.c

#----------

all: $(NAME)

$(NAME): $(LIBS) $(MLX_A) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) $(MLX_A) $(MLX_FLAGS) -o $(EXEC)
	@echo "\n$(GREEN)$(EXEC) created!$(DEFAULT)\n"

bonus: $(LIBS) $(MLX_A) $(BONUS_OBJECTS)
	@$(CC) $(CFLAGS) $(BONUS_OBJECTS) $(LIBS) $(MLX_A) $(MLX_FLAGS) -o $(EXEC)
	@echo "\n$(GREEN)$(EXEC) bonus created!$(DEFAULT)\n"
	@touch $@;

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
	@$(RM) $(BONUS_OBJECTS)
	@$(RM) $(BONUS_OBJECTS:.o=.d)
	make -C libft clean
	@cd $(MLX_DIR); make --no-print-directory clean

fclean: clean
	@$(RM) $(EXEC)
	@$(RM) $(LIBS)
	@$(RM) bonus
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