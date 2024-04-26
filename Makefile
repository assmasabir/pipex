# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabir <asabir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 20:13:19 by asabir            #+#    #+#              #
#    Updated: 2024/04/26 20:19:30 by asabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
NAME_BON = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g3

SRC = \
    pipex.c \
    libft_functions.c \
    libft_functions2.c \
    pipex_utils_1.c \
    pipex_utils_2.c \
    pipex_utils_3.c \
    pipex_utils_4.c \
    get_next_line/get_next_line.c \
    get_next_line/get_next_line_utils.c

SRC2 = \
    pipex_bonus.c \
    libft_functions2.c \
    libft_functions.c \
    pipex_utils_1.c \
    pipex_utils_2.c \
    pipex_utils_3.c \
    pipex_utils_4.c \
    get_next_line/get_next_line.c \
    get_next_line/get_next_line_utils.c

OBJS = $(SRC:.c=.o)
OBJB = $(SRC2:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(NAME_BON)

$(NAME_BON): $(OBJB)
	@$(CC) $(CFLAGS) $(OBJB) -o $(NAME_BON)

clean:
	@rm -rf $(OBJS) $(OBJB)

fclean: clean
	@rm -f $(NAME) $(NAME_BON)

re: fclean all

.PHONY: all fclean re clean bonus
