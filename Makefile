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

MAKEFLAGS += --no-print-directory

NAME = minishell

SRCS_PATH = ./src

FLAGS = -Werror -Wextra -Wall

SRC = main.c  env.c pwd.c  ft_tablen.c  unset.c \
	ft_addenv.c echo.c ft_find_env.c find_fst_split_arg_in_binary.c \
	print_prompt.c check_quote_close.c cat.c error.c show_welcome_mes.c \
	cmd_substitution.c get_full_cmd_path.c exit.c ft_signal.c \
	init_variable_sh.c manage_question_mark.c extract_cmd_from_bin_input.c \
	get_full_binary_path.c display_ascii_girafe.c \
	free_var.c manage_child_process_and_execution.c \
	manage_substitution_in_str.c manage_pipe.c  \
	check_export_var_val.c  export.c  show_export_var.c \
	cd.c check_cd_arg.c change_env_var_value.c  init_env_var.c \
	validity_sep_in_str.c split_fst_arg.c error_2.c maobe_util.c maobe_check_for_redir.c

SRC_PATH = $(addprefix $(SRCS_PATH)/,$(SRC))

OBJ = $(SRC:.c=.o)

CD_SRC = cd.c change_env_var_value.c init_env_var.c check_cd_arg.c \


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

OBJS_DIR    = ./objects

OBJS =${SRC:%.c=${OBJS_DIR}/%.o}

BLINK=\e[5m
RED=\033[91m
ORANGE=\e[38;5;202m
PURPLE=\e[38;5;57m
BLUE=\033[94m
DARK_YELLOW=\033[0;33m
YELLOW=\033[93m
GREEN=\033[0;32m
NC=\033[0;0m

${OBJS_DIR}/%.o: %.c
			@mkdir -p ${OBJS_DIR}
			@printf "${BLUE}MINISHELL${NC}:    ${DARK_YELLOW}Compilation...    ${YELLOW}%-15.15s${NC}\r" $(notdir ${<})
			@${CC} ${FLAGS} -I ${HEADER_DIR}  -c $< -o $@


${NAME}: header  ${OBJS}
	@printf "${BLUE}MINISHELL${NC}:    ${GREEN}Completed         ${YELLOW}----${NC}          \r\n"
	@make -C ./libft all
	@printf "${BLUE}LIBFT${NC}:        ${GREEN}Completed         ${YELLOW}----${NC}          \r\n"
	@${CC} ${FLAGS} ${OBJS} -L ./libft -lft -o ${NAME}
	@printf "\n${NC}⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤\n"
	@printf "${BLUE}MINISHELL${NC}:    ${GREEN}Ready             ${YELLOW}----          ${NC}\n"
	@printf "⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤\n"

	@echo "\n\n${RED}███╗   ███╗██╗ █████╗  ██████╗    ███╗   ███╗██╗ █████╗  ██████╗"
	@echo "${ORANGE}████╗ ████║██║██╔══██╗██╔═══██╗   ████╗ ████║██║██╔══██╗██╔═══██╗"
	@echo "${YELLOW}██╔████╔██║██║███████║██║   ██║   ██╔████╔██║██║███████║██║   ██║"
	@echo "${GREEN}██║╚██╔╝██║██║██╔══██║██║   ██║   ██║╚██╔╝██║██║██╔══██║██║   ██║"
	@echo "${BLUE}██║ ╚═╝ ██║██║██║  ██║╚██████╔╝   ██║ ╚═╝ ██║██║██║  ██║╚██████╔╝"
	@echo "${PURPLE}╚═╝     ╚═╝╚═╝╚═╝  ╚═╝ ╚═════╝    ╚═╝     ╚═╝╚═╝╚═╝  ╚═╝ ╚═════╝ ${NC}\n\n"
	@echo "\t\t    ${GREEN}${BLINK}${NAME} binary ready !!${NC}\n\n"



all: ${NAME}

header:
	@printf "${NC}⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤\n"
	@printf "PROJECT       ${NC}STATUS            FILE          ${NC}\n"
	@printf "⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤⏤\n"

libft_compile:
	@make -C ./libft all
	@printf "${BLUE}LIBFT${NC}:        ${GREEN}Completed         ${YELLOW}----${NC}          \r\n"
clean : libft_clean
		@rm -fr $(OBJ) $(CD_OBJ) $(EXP_OBJ) ${OBJS_DIR}
		@printf "${BLUE}PROJECT${NC}:      ${GREEN}Cleaned${NC}\n"

libft_clean:
		@make -C ./libft clean

fclean: clean libft_fclean
		@rm -f $(NAME)
		@rm -f **/*~
		@printf "${BLUE}Executable and object files removed${NC}\n"

libft_fclean:
		@make -C ./libft fclean

re: fclean all
