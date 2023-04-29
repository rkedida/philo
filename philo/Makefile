# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 13:55:48 by rkedida           #+#    #+#              #
#    Updated: 2023/04/29 16:18:08 by rkedida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

CFLAG		= -Wall -Wextra -Werror -g -pthread
HEADERS		= -I./includes
OBJ_DIR		= ./obj/

SRC_DIR		= ./
SRCS_FILES	= main.c parsing.c ft_atoi.c destroy.c init.c life_cycle.c utils.c

SRC			= $(addprefix $(SRC_DIR), $(SRCS_FILES))

OBJS_FILES	= $(addprefix $(OBJ_DIR), $(SRCS_FILES))
OBJS		= $(OBJS_FILES:.c=.o)

BOLD	= \033[1m
BLACK	= \033[30;1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

# //= Recipes =//

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAG) $(HEADERS) -c $< -o $@ && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(HEADERS) $(CFLAG) $(OBJS) -o $(NAME)

norm:
	@norminette

git:
	git add .
	git commit -m "Update"
	git push origin master

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re