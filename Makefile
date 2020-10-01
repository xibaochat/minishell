NAME = minishell

SRC = main.c

SRCS_PATH = ./src/

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

clean :
		rm -f $(OBJ)
		rm -f $(LIBFT_DIR)/*.o

fclean: clean
		rm -f $(NAME)
		rm -f $(LIBFT_A)
		rm -f ./*~ $(SRCS_PATH)*~ $(HEADER_DIR)/*~

re: fclean all
