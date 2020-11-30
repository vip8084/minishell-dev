# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmiso <hmiso@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 11:46:48 by hmiso             #+#    #+#              #
#    Updated: 2020/11/30 11:48:52 by hmiso            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

OBJ_FILES = 

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES) minishell.h
	gcc $(FLAG_LINK) $(OBJ_FILES) -o $(NAME)

%.o: %.c 
	gcc -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re