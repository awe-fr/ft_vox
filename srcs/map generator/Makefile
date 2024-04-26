NAME=map
CC=c++
FLAGS=-Wall -Werror -Wextra -g
SRCS=main.cpp MapGenerator.cpp

MLX_DIR = MLX42/
MLX_LIB = MLX42/build/libmlx42.a

$(NAME): $(MLX_LIB) $(OFILES)
	$(CC) $(FLAGS) -IMLX42/include -LMLX42/build $(SRCS) -o $(NAME) -lmlx42 -ldl -lglfw -pthread -lm

all : ${NAME}

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git

$(MLX_LIB): $(MLX_DIR)
	cd MLX42 && cmake -B build && cd build && make

clean :
	rm -rf ${NAME}

fclean :
	rm -rf ${NAME}

re : fclean all

.PHONY:  all clean fclean re