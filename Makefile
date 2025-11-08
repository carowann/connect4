# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/08 11:46:19 by cwannhed          #+#    #+#              #
#    Updated: 2025/11/08 17:37:51 by cwannhed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = connect4

SRC = src/main.c		\
	src/utils.c		\
	src/ai.c		\
	src/usage.c		\
	src/game_moves.c	\
	src/matrix_utils.c	\
	src/game_status.c	\

CFLAGS = -Wall -Wextra -Werror -g -std=c11

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I./includes -I./$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	@cc $(SRC) $(INCLUDES) $(CFLAGS) $(LIBFT) -o $(NAME)


$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)Cleaning $(NAME)...$(RESET)"
	@echo "$(RED)Clean completed!$(RESET)"

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)Full clean completed!$(RESET)"

re: fclean all

test: all
	./$(NAME) 7 6

val: re
	valgrind --leak-check=full ./$(NAME) 7

.PHONY: all clean fclean re test val

#colors
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m
