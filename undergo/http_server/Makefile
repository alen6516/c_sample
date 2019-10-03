all: http_server.out

CC = gcc
CFLAGS = -g -Wall -lpthread

http_server.out: main.c util.h func.h
	$(CC) $^ -o http_server.out $(CFLAGS)

