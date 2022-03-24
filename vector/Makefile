
SRCS		= 	main.cpp
OBJS		= 	$(SRCS:.cpp=.o)

CFLAGS		= 	-Wall -Wextra -Werror
CC			= 	g++

%.o :		%.cpp
			$(CC) -c -I../utils $(CFLAGS) $< -o $@

all:		vector

vector:	$(OBJS)
			$(CC) $(OBJS) -o vector

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re vector