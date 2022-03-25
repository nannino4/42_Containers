
NAME		=	main

SRCS		= 	main.cpp
OBJS		= 	$(SRCS:.cpp=.o)

CFLAGS		= 	-Wall -Wextra -Werror -g
CC			= 	g++

%.o :		%.cpp
			$(CC) -c -I../utils $(CFLAGS) $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re $(NAME)