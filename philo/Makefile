NAME = philo.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = 

OBJ = $(SRC:.c=.o)

RM = rm -rf 

AR = ar -rc

all : $(NAME)

$(NAME) : $(OBJ) philo.h
	$(AR) $(NAME) $(OBJ)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all