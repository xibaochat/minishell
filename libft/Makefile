#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/16 10:08:51 by xinwang           #+#    #+#              #
#    Updated: 2020/10/10 20:39:39 by maobe            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#.SILENT:

NAME = libft.a

HEADER_DIR = include

########
# MAIN #
########
SRCS_PATH = ./src

SRCS = ft_strcmp.c ft_atoi.c ft_split.c ft_bzero.c ft_strchr.c ft_calloc.c \
	ft_strdup.c ft_isdigit.c ft_strjoin.c ft_isalpha.c ft_memccpy.c \
	ft_strlcat.c ft_isascii.c ft_memchr.c ft_strlcpy.c  ft_isalnum.c \
	ft_memcmp.c ft_strlen.c ft_isprint.c ft_memcpy.c ft_strmapi.c ft_itoa.c \
	ft_memmove.c ft_strncmp.c ft_memset.c ft_strnstr.c ft_putchar_fd.c \
	ft_strtrim.c ft_putendl_fd.c ft_substr.c ft_putnbr_fd.c ft_tolower.c \
	ft_putstr_fd.c ft_toupper.c ft_strrchr.c  ft_putstr.c  get_next_line.c  \
	get_next_line_utils.c  ft_putchar.c  ft_putendl.c  ft_putstr_w_new_line.c \
	ft_strnew.c  ft_strcat.c ft_is_space.c ft_lstadd_back.c ft_lstadd_front.c \
	ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
	ft_lstnew.c ft_lstsize.c free_str.c free_p_str.c ft_strnew_with_char.c \
	ft_split_inc.c ft_strrmv.c ft_putstr_w_newline_fd.c ft_split_w_quotes.c \
	delete_quotes_from_arr.c delete_quotes_from_s.c init_quotes_struct.c \
	manage_struct_quotes.c escapted_char_management.c delete_slash_from_str.c \
	delete_slash_from_arr.c ft_tabfree.c ft_is_directory.c get_buffer.c show_arr_value.c \
	malloc_and_copy.c get_nb_size.c ft_rmv_elem.c ft_max_min.c




SRC_W_PATH = $(addprefix $(SRCS_PATH)/,$(SRCS))

SRCO = $(SRCS:.c=.o)

##########
# PRINTF #
##########

PRINTF_SRC = ft_printf.c is_conversion.c is_conversion_char.c \
	nb_char_to_skip.c do_conversion.c char_to_str.c ft_trans_x.c \
	ft_trans_capital_x.c ptr_to_str.c manage_flags.c apply_flags.c \
	ft_extract_value_flag.c copy_str_at.c apply_precision.c ft_apply_width.c \
	replace_star.c add_hex_chars.c has_invalide_char_in_flag.c \
	tweak_flags_values.c printf_value.c ft_initialize_flag.c get_size_int.c

PRINTF_PATH = $(SRCS_PATH)/printf

PRINTF_SRC_W_PATH = $(addprefix $(PRINTF_PATH)/,$(PRINTF_SRC))

PRINTF_SRCO = $(PRINTF_SRC:.c=.o)

##########
# COMMON #
##########

CC = gcc

CC_FLAGS = -Wall -Werror -Wextra



all: $(NAME)

$(NAME):
		@printf "Compiling Libft\n"
		@$(CC) $(CC_FLAGS) -c  $(SRC_W_PATH) $(PRINTF_SRC_W_PATH) -I $(HEADER_DIR)
		@ar rcs $(NAME) $(SRCO) $(PRINTF_SRCO)
		@printf "\033[1;32mLibft compiled\033[;0m\n"

clean:
		@rm -f $(SRCO) $(PRINTF_SRCO)

fclean: clean
		@rm -f $(NAME)

re: fclean all
