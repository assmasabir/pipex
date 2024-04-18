# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabir <asabir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 02:34:59 by asabir            #+#    #+#              #
#    Updated: 2024/04/11 16:09:17 by asabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC= cc 
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g3

SRC= \
	pipex.c				\
	libft_functions.c	\
	libft_finctions2.c	\
	pipex_utils_1.c		\
	pipex_utils_2.c		\
	pipex_utils_3.c		

SRC2=\
	pipex_bonus.c		\
	libft_finctions2.c	\
	libft_functions.c	\
	pipex_utils_1.c		\
	pipex_utils_2.c		\
	pipex_utils_3.c		\
	
OBJ1 = ${SRC:.c = .o}

all

$(NAME)

