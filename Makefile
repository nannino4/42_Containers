NAME			=	ft_containers
NAME_BONUS		=	ft_containers_bonus

SRCS			= 	main.cpp \
					tests/testVector.cpp \
					tests/testStack.cpp \
					tests/testMap.cpp
OBJS			= 	$(SRCS:.cpp=.o)

SRCS_BONUS		= 	main_bonus.cpp \
					tests/testVector.cpp \
					tests/testStack.cpp \
					tests/testMap.cpp \
					# tests/testSet.cpp
OBJS_BONUS		= 	$(SRCS_BONUS:.cpp=.o)

CFLAGS			= 	-Wall -Wextra -Werror
CC				= 	g++

%.o :			%.cpp
				$(CC) -c -I./tests -I./containers -I./utils $(CFLAGS) $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME)

bonus:			$(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_BONUS)
				$(CC) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:
				rm -f $(OBJS_BONUS)

fclean:			clean
				rm -f $(NAME) $(NAME_BONUS)

re:				fclean all

.PHONY:			all clean fclean re $(NAME) bonus $(NAME_BONUS)