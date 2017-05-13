# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/26 16:28:09 by edeveze           #+#    #+#              #
#    Updated: 2017/04/26 19:01:20 by edeveze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME = libftprintf.a

# Includes
INC = -I includes/ -I libft/includes
# Files
SRC = test.c\
	parsing.c\
	checking.c\
	error.c\
	type.c\
	displaying.c\

# Objects
OBJ = $(SRC:.c=.o)

# Compilation
CFLAGS = -Wall -Wextra -Werror -g
PRGFLAGS = -L libft/ -framework AppKit libft/libft.a

# Rules
all : lib $(NAME)

lib:
	@make -C libft/ fclean
	@make -C libft

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(PRGFLAGS) -o $@ $(OBJ)

%.o: %.c libft/libft.a
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	@rm -rf $(OBJ)
	@make -C libft clean

fclean : clean
	@rm -rf $(NAME)
	@make -C libft fclean

re : fclean all

.PHONY: all clean fclean re