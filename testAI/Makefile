
CC			=	g++

RM			=	rm -f

INCLUDES	=	-I../API

CPPFLAGS	+=	-Wall -Wextra -std=c++1z -O2 $(INCLUDES)

NAME	=	testAI

SRCS	=	main.cpp	\
			testAPI.cpp	\

OBJS	=	$(SRCS:.cpp=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) -o $(NAME) $(CPPFLAGS) $(OBJS)

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all