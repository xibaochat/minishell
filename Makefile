#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maobe <maobe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/01 10:13:39 by maobe             #+#    #+#              #
#    Updated: 2020/10/17 23:20:02 by maobe            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = minishell

SRCS_PATH = ./src

SRC = main.c  env.c pwd.c  ft_tablen.c  unset.c \
	ft_addenv.c echo.c ft_find_env.c find_fst_split_arg_in_binary.c \
	print_prompt.c check_quote_close.c cat.c error.c show_welcome_mes.c \
	cmd_substitution.c get_full_cmd_path.c exit.c ft_signal.c \
	init_variable_sh.c manage_question_mark.c extract_cmd_from_bin_input.c \
	get_full_binary_path.c \
	free_var.c manage_child_process_and_execution.c manage_syntax_error.c \
	manage_substitution_in_str.c redirections.c manage_pipe.c

SRC_PATH = $(addprefix $(SRCS_PATH)/,$(SRC))

OBJ = $(SRC:.c=.o)

CD_SRC = cd.c change_env_var_value.c init_env_var.c	check_cd_arg.c \


CD_PATH = $(addprefix $(SRCS_PATH)/,$(addprefix manage_cd/,$(CD_SRC)))

CD_OBJ =  $(CD_SRC:.c=.o)

EXP_SRC = check_export_var_val.c export.c show_export_var.c \

EXP_PATH = $(addprefix $(SRCS_PATH)/,$(addprefix export/,$(EXP_SRC)))

EXP_OBJ =  $(EXP_SRC:.c=.o)

CC = gcc

HEADER_DIR = include

LIBFT_DIR = libft

LIBFT_A = $(LIBFT_DIR)/libft.a

LIBFT_HEADER = $(LIBFT_DIR)/include

all : ${NAME}

${NAME}: libft_compile
	$(CC) -c $(SRC_PATH) $(CD_PATH) $(EXP_PATH) -I $(HEADER_DIR) -I $(LIBFT_HEADER) -L $(LIBFT_DIR) -lft
	$(CC) $(OBJ) $(CD_OBJ) $(EXP_OBJ) -o ${NAME} -L $(LIBFT_DIR) -lft

libft_compile:
	make -C ./libft all --silent

clean : libft_clean
		rm -f $(OBJ) $(CD_OBJ) $(EXP_OBJ)

libft_clean:
		make -C ./libft clean

fclean: clean libft_fclean
		rm -f $(NAME)
		rm -f **/*~

libft_fclean:
		make -C ./libft fclean

re: fclean all
