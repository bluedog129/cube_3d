# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 12:05:39 by hyojocho          #+#    #+#              #
#    Updated: 2023/07/09 12:42:39 by choihyojong      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SOURCES = ft_bzero.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_strchr.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_tolower.c ft_toupper.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c \
			ft_substr.c ft_strnstr.c ft_memcmp.c \
			ft_strjoin.c ft_strtrim.c ft_split.c \
			ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_htoa.c ft_utoa.c ft_uitoa.c \
			ft_uitoa_lower.c ft_strcmp.c ft_atol.c ft_atoi_extension.c \
			./get_next_line/get_next_line.c \
			./get_next_line/get_next_line_utils.c

OBJECT = $(SOURCES:.c=.o)
B_OBJECT = $(B_SOURCES:.c=.o)
P_OBJECT = $(FT_PRINTF:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(OBJECT) $(B_OBJECT) $(P_OBJECT)
else
	OBJECTS = $(OBJECT) $(P_OBJECT)
endif

all : $(NAME)

$(NAME) : $(OBJECTS)
	@ar rcs $@ $^
	@echo "$(GREEN)LIBFT created!$(DEFAULT)"

.c.o :
	@cc $(CFLAGS) -c $< -o $(<:.c=.o)
bonus :
	make WITH_BONUS=1 all
	
clean :
	@rm -rf $(OBJECT) $(B_OBJECT) $(P_OBJECT)

fclean : clean
	@rm -rf $(NAME)
	@echo "$(BLUE)LIBFT delete all!$(DEFAULT)"

re :
	@make fclean
	@make all

.PHONY : all clean fclean re

RED = \033[1;31m
PINK = \033[1;35m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
DEFAULT = \033[0m