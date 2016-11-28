# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csummers <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/21 14:37:39 by csummers          #+#    #+#              #
#    Updated: 2016/11/21 14:37:40 by csummers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = fillit.c read.c list_helpers.c map_helpers.c block_helpers.c

OBJ = $(SRC:.c=.o)

HDR = -I.

LIB = -L./ -lft

CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) $(HDR) -c $(SRC)
	gcc $(CFLAGS) $(OBJ) $(HDR) $(LIB) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all