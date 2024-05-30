# Compiler and compiler flags
CC = gcc
CFLAGS = -std=c11 -Wall -g

# Name of the executable
EXE = FindComponents

# Object files
OBJS = FindComponents.o Graph.o List.o

# Default target
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

# Compile FindComponents.c
FindComponents.o: FindComponents.c Graph.h List.h
	$(CC) $(CFLAGS) -c FindComponents.c

# Compile Graph.c
Graph.o: Graph.c Graph.h List.h
	$(CC) $(CFLAGS) -c Graph.c

# Compile List.c
List.o: List.c List.h
	$(CC) $(CFLAGS) -c List.c

# Target to run the program with Valgrind
valgrind: $(EXE)
	valgrind --leak-check=full ./$(EXE)

# Clean target
clean:
	rm -f $(EXE) $(OBJS)

