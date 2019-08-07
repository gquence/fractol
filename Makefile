CC = gcc
FLAGS =  -Wextra -Werror -Wall

MLX_FLAGS = -I /usr/local/include -L /usr/local/lib/  -framework OpenGL -framework AppKit

SRC_DIR = 
INC_DIR = .
SRCS = init_cl.c main.c fract_init.c get_color.c utils.c

OBJ = $(SRCS:.c=.o)

LIB_INC = libft/includes
LIB_DIR = libft/
LIB_NAME = libft.a

MLX_DIR  = minilibx_macos/
MLX_NAME = libmlx.a
MLX_INT = minilibx_macos/
NAME = fractol
OBJ_DIR = ./obj/

all: $(LIB_NAME) $(NAME) 

$(LIB_NAME):
	make -C $(LIB_DIR) $(LIB_NAME)

$(MLX_NAME):
	make -C $(MLX_DIR) $(MLX_NAME)

$(NAME): $(MLX_NAME)
	$(CC) -c $(SRC_DIR)$(SRCS) -I $(INC_DIR) -I $(LIB_INC) $(FLAGS)
	$(CC) $(OBJ)  -o $(NAME) -L $(LIB_DIR) -lft  $(MLX_FLAGS) -L $(MLX_DIR) -l mlx -framework OpenCL

clean:
	rm -rf $(OBJ) $(OBJ_READ)
	make -C $(LIB_DIR) clean
	make -C $(MLX_DIR) clean
	
fclean: clean
	rm -rf $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all
