# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gquence <gquence@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 05:49:36 by dmelessa          #+#    #+#              #
#    Updated: 2019/05/08 17:53:54 by gquence          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRC_DIR = srcs/
INC_DIR = includes/
PREFIX = ft_
SRC = get_next_line.c $(addprefix $(PREFIX), \
	memset.c bzero.c memcpy.c memccpy.c memmove.c memchr.c memcmp.c strlen.c \
	strnlen.c strdup.c strcpy.c strncpy.c strcat.c strncat.c strlcat.c \
	strchr.c strrchr.c strstr.c strnstr.c strcmp.c strncmp.c atoi.c isalpha.c \
	isdigit.c isalnum.c isascii.c isprint.c toupper.c tolower.c islower.c isupper.c \
	memalloc.c memdel.c strnew.c strdel.c strclr.c striter.c striteri.c strmap.c \
	strmapi.c strequ.c strnequ.c strsub.c strjoin.c strtrim.c strsplit.c itoa.c \
	putchar.c putstr.c putendl.c putnbr.c putchar_fd.c putstr_fd.c putendl_fd.c \
   putnbr_fd.c lstnew.c lstdelone.c lstdel.c lstadd.c lstiter.c lstmap.c isspace.c\
   strndup.c sqrt.c ishex.c atoi_base.c)
FLAGS = -Wall -Wextra -Werror
NAME = libft.a
OBJ=$(SRC:.c=.o)

all : $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC) -I $(INC_DIR)
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
