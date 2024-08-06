NAME = ft_vox

SRCS = srcs/main.cpp \
		srcs/Model/Biome.cpp \
		srcs/Model/Block.cpp \
		srcs/Model/Model.cpp \
		srcs/Model/BlockMap.cpp \
		srcs/Model/NoiseMap.cpp \
		srcs/Model/SimplexNoise.cpp \
		srcs/Model/BlockMapChunk.cpp \
		srcs/Model/NoiseMapChunk.cpp \
		srcs/View/stb.cpp \
		srcs/View/View.cpp \
		srcs/View/Skybox.cpp \
		srcs/View/ViewMap.cpp \
		srcs/View/ViewChunk.cpp \
		srcs/View/WindowApp.cpp \
		srcs/View/PlayerInfo.cpp \
		srcs/View/ShaderLoader.cpp \
		srcs/Controller/Controller.cpp \

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -pthread -Wall -Wextra -Werror

LDFLAGS = -Iinclude -I/usr/local/include/glm/glm -Llib -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -lXi -ldl -D GLEW_STATIC

all: 		$(NAME)

include/View/stb_image.h:
	git clone https://github.com/awe-fr/lib.git
	cp lib/stb_image.h include/View
	rm -rf lib

$(NAME): include/View/stb_image.h
		g++ $(CFLAGS) -o $(NAME) $(SRCS) $(LDFLAGS) -g -O3

test: 		$(NAME)
		./$(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -rf include/View/stb_image.h
		rm -f $(NAME)

re:		fclean all

.PHONY: all test clean fclean re
