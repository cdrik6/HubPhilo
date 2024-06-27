# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 23:32:02 by caguillo          #+#    #+#              #
#    Updated: 2024/06/28 01:13:00 by caguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS		=	srcs/main.c \
				srcs/init.c \
				srcs/thread.c \
				srcs/routine.c \
				srcs/monitor.c \
				srcs/tools.c

INCS_SRCS	=	./includes/phi.h
				
INCS_DIR	=	-Iincludes

CC			=	gcc
#CFLAGS		=	-Wall -Wextra -Werror -pthread -D MAX_PHILO=200
CFLAGS		=	-Wall -Wextra -Werror -pthread -fsanitize=thread -g
#CFLAGS		=	-Wall -Wextra -Werror -pthread -g 

OBJS		=	$(SRCS:.c=.o)

%.o:%.c		$(INCS_SRCS)
			$(CC) $(CFLAGS) $(INCS_DIR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			
all:		$(NAME)

re: 		fclean all

bonus:		$(NAME)

rebonus: 	fclean bonus
			
clean:
			rm -f $(OBJS)
			
fclean: 	clean
			rm -f $(NAME)

.PHONY: 	all clean fclean re bonus rebonus
