#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/16 10:08:51 by xinwang           #+#    #+#              #
#    Updated: 2020/10/09 21:22:02 by maobe            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.SILENT:

NAME = libft.a

HEADER_DIR = include

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
	ft_lstnew.c ft_lstsize.c

SRC_W_PATH = $(addprefix $(SRCS_PATH)/,$(SRCS))

SRCO = $(SRCS:.c=.o)


CC = gcc

CC_FLAGS = -Wall -Werror -Wextra



all: $(NAME)

$(NAME):
		$(CC) $(CC_FLAGS) -c  $(SRC_W_PATH) -I $(HEADER_DIR)
		ar rcs $(NAME) $(SRCO)

clean:
		 rm -f $(SRCO)

fclean: clean
		rm -f $(NAME)

re: fclean all
