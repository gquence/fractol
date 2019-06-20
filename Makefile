CC = gcc
FLAGS = -lmlx -framework OpenGL -framework AppKit
FLAGS_LINUX = -l mlx -L /usr/lib/x86_64-linux-gnu/ -l Xext -l m -l X11
SRC_DIR = 
INC_DIR = -I . -I libft/includes/
SRCS = draw_line.c main.c  reading/*.c libft/libft.a
OBJ = $(SRCS:.c=.o)
NAME = fdf
LIB = make -C libft/ re

all: $(LIB) 
	gcc main.c loading.c julia.c draw_line.c  reading/*.c  libft/libft.a -I . -I libft/includes/ -lmlx -framework OpenGL -framework AppKit


allL:
	make -C minilibx -f Makefile.gen all
	$(LIB)
	gcc main.c loading.c draw_line.c  reading/*.c  libft/libft.a  $(FLAGS) $(INC_DIR)

	
clean:
	rm -rf $(NAME)

re: clean all
