# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: praders <praders@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 16:34:39 by mprazere          #+#    #+#              #
#    Updated: 2025/07/07 14:14:17 by praders          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
PHILO_A = libphilo.a

SRCS = #srcs/ srcs/ srcs/ srcs/  \

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs

all: $(PHILO_A) $(NAME)

$(PHILO_A): $(OBJS)
	@$(AR) $(PHILO_A) $(OBJS)
	@echo 'Biblioteca libphilo.a criada!'

$(NAME): $(OBJS) $(MAIN)
	@$(CC) $(CFLAGS) $(OBJS) -lft -o $(NAME)
	@echo 'philo compilado!'

clean:
	@rm -f $(OBJS)
	@rm -f $(PHILO_A)
	@echo 'Objetos limpos!'

fclean: clean
	@rm -f $(NAME)
	@echo 'Tudo limpo!'

re: fclean all

.PHONY: all clean fclean re
