NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRC = main.c utils.c

OBJ = $(SRC:.c=.o)

RM = rm -rf 

all : $(NAME)

$(NAME) : $(OBJ) philo.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all