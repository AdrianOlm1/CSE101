# Makefile for List program

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Source files
SRCS = List.c Lex.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = Lex

# Main target
all: $(EXEC)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Run valgrind to check for memory leaks
valgrind: $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

# Clean up
clean:
	rm -f $(OBJS) $(EXEC)

