NAME = ft_vox

SRCS = srcs/*.cpp

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -Iinclude -Llib -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -lXi -ldl -D GLEW_STATIC

all: 		$(NAME)

$(NAME):	$(OBJS)
		g++ $(CFLAGS) -o $(NAME) $(SRCS) $(LDFLAGS) -g

test: 		$(NAME)
		./$(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all test clean fclean re