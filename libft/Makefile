# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmiso <hmiso@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/18 20:15:21 by hmiso             #+#    #+#              #
#    Updated: 2020/05/21 19:40:49 by hmiso            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
OBJ_FILES = ft_memset.o \
			ft_bzero.o \
			ft_memcpy.o \
			ft_memccpy.o \
			ft_memmove.o \
			ft_memchr.o \
			ft_memcmp.o \
			ft_strlen.o \
			ft_strlcpy.o \
			ft_strlcat.o \
			ft_strchr.o \
			ft_strrchr.o \
			ft_strnstr.o \
			ft_strncmp.o \
			ft_isalpha.o \
			ft_isdigit.o \
			ft_isalnum.o \
			ft_isascii.o \
			ft_isprint.o \
			ft_toupper.o \
			ft_tolower.o \
			ft_calloc.o \
			ft_strdup.o \
			ft_atoi.o \
			ft_substr.o \
			ft_strjoin.o \
			ft_strtrim.o \
			ft_split.o \
			ft_itoa.o \
			ft_strmapi.o \
			ft_putchar_fd.o \
			ft_putstr_fd.o \
			ft_putendl_fd.o \
			ft_putnbr_fd.o 

BONUSO =	ft_lstnew.o \
			ft_lstadd_front.o \
			ft_lstsize.o \
			ft_lstlast.o \
			ft_lstadd_back.o \
			ft_lstdelone.o \
			ft_lstclear.o  \
			ft_lstiter.o

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES) libft.h
	ar rc $(NAME) $(OBJ_FILES) $^
	ranlib $(NAME)

bonus: $(BONUSO) $(OBJ_FILES) libft.h
	ar rc $(NAME) $(BONUSO) $(OBJ_FILES) $^
	ranlib $(NAME)

%.o: %.c 
	gcc -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(BONUSO)

fclean: clean
	rm -f $(NAME)

re: fclean all
