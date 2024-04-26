NAME=map
CC=c++
FLAGS=-Wall -Werror -Wextra -g
SRCS=main.cpp MapGenerator.cpp

${NAME} :
	$(CC) ${FLAGS} $(SRCS) -o $(NAME)

all : ${NAME}

clean :
	rm -rf ${NAME}

fclean :
	rm -rf ${NAME}

re : fclean all