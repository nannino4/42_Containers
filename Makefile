
VECTOR_SRCS		= 	
VECTOR_OBJS		= 	$(SRCS:.cpp=.o)

STACK_SRCS		= 	
STACK_OBJS		= 	$(SRCS:.cpp=.o)

MAP_SRCS		= 	
MAP_OBJS		= 	$(SRCS:.cpp=.o)

CFLAGS		= 	-Wall -Wextra -Werror
CC			= 	g++

%.o :		%.cpp
			$(CC) -c -I./vector -I./utils $(CFLAGS) $< -o $@

all:		vector stack map

vector:	$(VECTOR_OBJS)
			$(CC) $(VECTOR_OBJS) -o vector

stack:	$(STACK_OBJS)
			$(CC) $(STACK_OBJS) -o stack

map:	$(MAP_OBJS)
			$(CC) $(MAP_OBJS) -o map

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)


re:			fclean all

.PHONY:		all clean fclean re vector stack map