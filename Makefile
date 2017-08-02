# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/26 16:28:09 by edeveze           #+#    #+#              #
#    Updated: 2017/08/02 19:37:02 by edeveze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = ft_printf.c\
	buffer.c\
	checking.c\
	type.c\
	digit_values.c\
	displaying.c\
	display_digit.c\
	display_char.c\
	display_wchar.c\
	modif_str.c\
	parsing.c\
	verifications.c\
	wstr_functions.c\
	

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -O3

INC = includes

SRC_PATH = srcs
OBJ_PATH = obj
LIBFT_PATH = libft
LIBFTA = libft.a
LIBFT = $(addprefix $(LIBFT_PATH)/,$(LIBFTA))
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJS = $(addprefix $(OBJ_PATH)/,$(SRC_NAME:.c=.o))

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

all: $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@gcc $(FLAGS) -I $(INC) -o $@ -c $<

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	@cp $(LIBFT) ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "$(GREEN)--------ft_printf compiled--------$(NC)"

clean:
	@make clean -C $(LIBFT_PATH)
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@/bin/rm -rf $(NAME)
	@echo "$(GREEN)---ft_printf removed completely---$(NC)"

re: fclean all