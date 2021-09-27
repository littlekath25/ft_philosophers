# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: katherine <katherine@student.codam.nl>       +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/13 11:32:28 by katherine     #+#    #+#                  #
#    Updated: 2021/09/27 11:36:55 by kfu           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= 	philo_bonus
CC			= 	gcc
RM			=	rm -f
CFLAGS		= 	-Wall -Wextra -g3 -fsanitize=address -pthread

LIBS		=	-o

SRC			= 	main.c\
				parsing.c\
				utils.c\
				routine.c\
				init.c
OBJ			=	$(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(NAME) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I includes/

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all