CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
TARGET = bin/main
SRC = src/main.c src/glad.c src/window.c src/callback.c src/shader.c src/buffer.c src/stb_image.c src/texture.c src/transform.c

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) -I ./include -o $@ $^
