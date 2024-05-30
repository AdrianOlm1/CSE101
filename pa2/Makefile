CC = gcc
CFLAGS = -Wall -std=c99
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

# List of source files
SRCS = FindPath.c List.c Graph.c

# List of object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = FindPath

# Main target
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program with valgrind for memory debugging
valgrind: $(EXEC)
	$(VALGRIND) ./$(EXEC)

# Clean target to remove generated files
clean:
	rm -f $(OBJS) $(EXEC)

