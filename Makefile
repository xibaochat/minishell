#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maobe <maobe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/01 10:13:39 by maobe             #+#    #+#              #
#    Updated: 2020/10/03 03:47:47 by maobe            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = minishell

SRCS_PATH = ./src

SRC = main.c display_ascii_dude.c env.c pwd.c  ft_tablen.c \

SRC_PATH = $(addprefix $(SRCS_PATH)/,$(SRC))

OBJ = $(SRC:.c=.o)

CD_SRC = cd.c cd_options.c manage_cd_opt.c change_env_var_value.c

CD_PATH = $(addprefix $(SRCS_PATH)/,$(addprefix cd/,$(CD_SRC)))

CD_OBJ =  $(CD_SRC:.c=.o)

EXP_SRC = check_export_var_val.c export.c show_export_var.c

EXP_PATH = $(addprefix $(SRCS_PATH)/,$(addprefix export/,$(EXP_SRC)))

EXP_OBJ =  $(EXP_SRC:.c=.o)

CC = gcc

HEADER_DIR = include

LIBFT_DIR = libft

LIBFT_A = $(LIBFT_DIR)/libft.a

all : ${NAME}

${NAME}: libft_compile
	$(CC) -c $(SRC_PATH) $(CD_PATH) $(EXP_PATH) -I $(HEADER_DIR) -L $(LIBFT_DIR) -lft
	$(CC) $(OBJ) $(CD_OBJ) $(EXP_OBJ) -o ${NAME} -L $(LIBFT_DIR) -lft

libft_compile:
	make -C ./libft all --silent

clean : libft_clean
		rm -f $(OBJ) $(CD_OBJ) $(EXP_OBJ)

libft_clean:
		make -C ./libft clean

fclean: clean libft_fclean
		rm -f $(NAME)
		rm -f ./*~ $(SRCS_PATH)*~ $(CD_PATH)*~ $(EXP_PATH)*~  $(HEADER_DIR)/*~

libft_fclean:
		make -C ./libft fclean

re: fclean all
