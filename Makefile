NAME = scop

GLEW = lib/glew/2.2.0_1
LIB_GLEW = libGLEW.2.2.0.dylib
GLFW = lib/glfw/3.3.4
LIB_GLFW = libglfw.3.dylib

HDRS = -I./include -I./$(GLEW)/include -I./$(GLFW)/include
SRCS = \
	source/main.c \
	source/dsUtils.c \
	source/loadShader.c \
	source/dsgm.c 
OBJS = $(SRCS:.c=.o)

CC = gcc
FLAG = -Wall -Werror -Wextra
FRAMEWORK = -framework OpenGL

all: $(NAME)

$(NAME): $(OBJS)
	cp $(GLEW)/lib/$(LIB_GLEW) $(LIB_GLEW)
	cp $(GLFW)/lib/$(LIB_GLFW) $(LIB_GLFW)
	$(CC) $(FLAG) $(FRAMEWORK) $(HDRS) $(LIB_GLEW) $(LIB_GLFW) $^ -o $(NAME)

%.o: %.c
	$(CC) $(FLAG) $(HDRS) -o $@ -c $<

clean:
	rm -f $(OBJS) $(LIB_GLEW) $(LIB_GLFW)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	./$(NAME)