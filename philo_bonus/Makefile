# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 15:02:42 by ssawane           #+#    #+#              #
#    Updated: 2022/04/13 15:57:17 by ssawane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus
			
SRCS		=	main_bonus.c	philo_utils.c	processing_bonus.c\

HEADER		=	philo_bonus.h

OBJ			=	$(SRCS:%.c=%.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

bonus		:	all

$(NAME)		:	$(OBJ) $(HEADER)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o			:		%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@

clean		:
				@rm -f $(OBJ) $(OBJ_B)

fclean		:	clean
				@$(RM) $(NAME) $(NAME_B)

re			:	fclean all
