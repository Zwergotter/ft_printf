# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edeveze <edeveze@marvin42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/26 16:28:09 by edeveze           #+#    #+#              #
#    Updated: 2017/06/27 16:50:32 by edeveze          ###   ########.fr        #
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
	display_num.c\
	display_str.c\
	display_w.c\
	verifications.c\
	buffer.c\

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

# 	SRC_NAME = ft_printf.c\
# 	parsing.c\
# 	checking.c\
# 	error.c\
# 	type.c\
# 	displaying.c\
# 	display_num.c\
# 	display_str.c\
# 	display_w.c\
# 	verifications.c\

# NAME = libftprintf.a

# FLAGS = -Wall -Wextra -Werror

# INC = includes

# SRC_PATH = srcs
# OBJ_PATH = obj
# LIBFT_PATH = libft
# LIBFTA = libft.a
# LIBFT = $(addprefix $(LIBFT_PATH)/,$(LIBFTA))
# SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
# OBJS = $(addprefix $(OBJ_PATH)/,$(SRC_NAME:.c=.o))

# GREEN = \033[0;32m
# RED = \033[0;31m
# NC = \033[0m

# all: $(NAME)

# $(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
# 	@mkdir -p $(OBJ_PATH)
# 	@gcc $(FLAGS) -I $(INC) -o $@ -c $<

# $(NAME): $(OBJS)
# 	@make -C $(LIBFT_PATH)
# 	@cp $(LIBFT) ./$(NAME)
# 	@ar rc $(NAME) $(OBJS)
# 	@ranlib $(NAME)
# 	@echo "$(GREEN)--------ft_printf compiled--------$(NC)"

# clean:
# 	@make clean -C $(LIBFT_PATH)
# 	@/bin/rm -rf $(OBJ_PATH)

# fclean: clean
# 	@make fclean -C $(LIBFT_PATH)
# 	@/bin/rm -rf $(NAME)
# 	@echo "$(GREEN)---ft_printf removed completely---$(NC)"

