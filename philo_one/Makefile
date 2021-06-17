# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmontagu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 21:21:08 by jmontagu          #+#    #+#              #
#    Updated: 2020/10/31 21:30:10 by jmontagu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo_one

PHILO 		= philo_one.h


SRC = main.c ft_atoi.c util_func.c init.c

GCC 	= gcc
RM 		= rm -f
CFLAGS	= -Wall -Wextra -Werror 

.%c.o:
	$(GCC) $(CFLAGS) $< -o ${<:.c=.o}

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
		make -C ./libft/

$(NAME): $(OBJS)
	$(GCC) -o $(NAME) $(OBJS)

clean:
	$(RM) *.o *.gch

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 