# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: katherine <katherine@student.codam.nl>       +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/09 15:35:47 by katherine     #+#    #+#                  #
#    Updated: 2021/08/30 17:59:52 by katherine     ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= 	philo
CC			= 	gcc
RM			=	rm -f
CFLAGS		= 	-Wall -Wextra -g3 -fsanitize=address -pthread

LIBS		=	-o

SRC			= 	main.c\
				utils.c\
				parsing.c\
				create.c\
				routine.c
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