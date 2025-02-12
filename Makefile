CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
TARGET = bin/main
SRC = src/main.c src/glad.c

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) -I ./include -o $@ $^
