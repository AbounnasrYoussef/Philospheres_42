NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=thread
SRC = init.c main.c routine.c time.c utiles.c  philosophe.c
OBJ         = $(SRC:.c=.o)
RM          = rm -f

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


