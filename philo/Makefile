# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 15:02:42 by ssawane           #+#    #+#              #
#    Updated: 2022/04/13 16:02:18 by ssawane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
			
SRCS		=	main.c	philo_utils.c	processing.c\

HEADER		=	philo.h

OBJ			=	$(SRCS:%.c=%.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

.PHONY		:	all clean fclean re

all			:	$(NAME)

$(NAME)		:	$(OBJ) $(HEADER)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o			:		%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@

clean		:
				@rm -f $(OBJ) $(OBJ_B)

fclean		:	clean
				@$(RM) $(NAME) $(NAME_B)

re			:	fclean all
