# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: martin <martin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/21 11:29:48 by martin            #+#    #+#              #
#    Updated: 2026/03/21 17:03:21 by martin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = codexion
CC          = cc
FLAGS       = -Wall -Werror -Wextra -pthread

SRC_DIR     = coders/
OBJ_DIR     = obj/

SRC_FILES   = main.c \
              check_value.c \
			  utils.c \
			  simulation.c \
			  cleanup.c \
			  init_ressources.c \

SRC         = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ         = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re