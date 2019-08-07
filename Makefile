CC = gcc
FLAGS =  -Wextra -Werror -Wall

MLX_FLAGS = -I /usr/local/include -L /usr/local/lib/  -framework OpenGL -framework AppKit

SRC_DIR = ./srcs
INC_DIR = ./includes/
SRCS = init_cl.c main.c fract_init.c get_color.c utils.c
OBJS = $(SRCS:.c=.o)


LIB_INC = libft/includes
LIB_DIR = libft/
LIB_NAME = libft.a

MLX_DIR  = minilibx_macos/
MLX_NAME = libmlx.a
MLX_INT = minilibx_macos/
NAME = fractol
OBJ_DIR = ./obj

SRC = $(addprefix $(SRC_DIR)/,$(SRCS))
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJS))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR) $(LIB_NAME)
	make -C $(MLX_DIR) $(MLX_NAME)
	$(CC) $^ -o $@ -L $(LIB_DIR) -lft  $(MLX_FLAGS) -L $(MLX_DIR) -l mlx -framework OpenCL

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@ -I $(LIB_INC) -I $(INC_DIR)

clean:
	rm -rf $(OBJ) $(OBJ_READ)
	make -C $(LIB_DIR) clean
	make -C $(MLX_DIR) clean
	
fclean: clean
	rm -rf $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all
