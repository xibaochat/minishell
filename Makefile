#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maobe <maobe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/01 10:13:39 by maobe             #+#    #+#              #
#    Updated: 2020/10/02 02:24:14 by maobe            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = minishell

SRCS_PATH = ./src

SRC = main.c display_ascii_dude.c ft_envadd.c env.c pwd.c cd.c ft_tablen.c \
	cd_options.c manage_cd_opt.c

SRC_PATH = $(addprefix $(SRCS_PATH)/,$(SRC))

OBJ = $(SRC:.c=.o)

CC = gcc

HEADER_DIR = include

LIBFT_DIR = libft

LIBFT_A = $(LIBFT_DIR)/libft.a

all : ${NAME}

${NAME}: libft_compile
	$(CC) -c $(SRC_PATH) -I $(HEADER_DIR) -L $(LIBFT_DIR) -lft
	$(CC) ${OBJ} -o ${NAME} -L $(LIBFT_DIR) -lft

libft_compile:
	make -C ./libft all --silent

clean : libft_clean
		rm -f $(OBJ)

libft_clean:
		make -C ./libft clean

fclean: clean libft_fclean
		rm -f $(NAME)
		rm -f ./*~ $(SRCS_PATH)*~ $(HEADER_DIR)/*~

libft_fclean:
		make -C ./libft fclean

re: fclean all
