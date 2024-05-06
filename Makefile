NAME = ft_vox

SRCS = srcs/main.cpp \
		srcs/Model/Biome.cpp \
		srcs/Model/Block.cpp \
		srcs/Model/BlockMap.cpp \
		srcs/Model/BlockMapChunk.cpp \
		srcs/Model/Model.cpp \
		srcs/Model/NoiseMap.cpp \
		srcs/Model/NoiseMapChunk.cpp \
		srcs/View/PlayerInfo.cpp \
		srcs/View/ShaderLoader.cpp \
		srcs/View/stb.cpp \
		srcs/View/View.cpp \
		srcs/View/ViewChunk.cpp \
		srcs/View/ViewMap.cpp \
		srcs/View/WindowApp.cpp \
		srcs/View/Skybox.cpp \
		srcs/Controller/Controller.cpp \

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -Wall -Wextra -Werror -pthread

LDFLAGS = -Iinclude -I/usr/local/include/glm/glm -Llib -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -lXi -ldl -D GLEW_STATIC

all: 		$(NAME)

$(NAME):
		g++ $(CFLAGS) -o $(NAME) $(SRCS) $(LDFLAGS) -g

test: 		$(NAME)
		./$(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all test clean fclean re