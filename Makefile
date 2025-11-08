# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/08 10:30:53 by cwannhed          #+#    #+#              #
#    Updated: 2025/11/08 10:37:04 by cwannhed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = connect4

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I./includes -I./$(LIBFT_DIR)

SRC =	src/main.c		\

FLAGS	= -g
FLAGS	+= -Wall -Werror -Wextra

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRC)
	@cc $(SRC) $(INCLUDES) $(CFLAGS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t compilation completed$(RESET)"

clean:
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(RED)[$(NAME)]:\t clean$(RESET)"

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(RED)[$(NAME)]:\t fclean$(RESET)"

re: fclean all

.PHONY: all clean fclean re