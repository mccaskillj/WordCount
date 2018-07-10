# Flags for compiling
CC = gcc
CFLAGS = -Wall -std=c99

# Compile all programs
all: word_count http_server

word_count: word_count.o lists.o
	$(CC) $(CFLAGS) $^ -g -o word_count

word_count.o: word_count.c word_count.h
	$(CC) $(CFLAGS) -g -c $^

lists.o: lists.c lists.h
	$(CC) $(CFLAGS) -g -c $^