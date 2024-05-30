# Compiler
CC=gcc

# Compiler flags
CFLAGS=-std=c99 -Wall -Wextra -pedantic

# Valgrind options
VALGRIND=valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

# Object files
OBJS=List.o Matrix.o Sparse.o

# Executable name
EXE=Sparse

# Compile and build the executable
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

# Compile the source files into object files
List.o: List.c List.h
	$(CC) $(CFLAGS) -c List.c

Matrix.o: Matrix.c Matrix.h
	$(CC) $(CFLAGS) -c Matrix.c

Sparse.o: Sparse.c List.h Matrix.h
	$(CC) $(CFLAGS) -c Sparse.c

# Run the program with Valgrind
memcheck: $(EXE)
	$(VALGRIND) ./$(EXE)

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(EXE)

# Phony targets
.PHONY: clean memcheck

