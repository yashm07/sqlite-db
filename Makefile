# Makefile for my_project

# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall  # -I to include the "include/" directory, -Wall to enable all warnings

# Source files and object files
SRC = src/main.c src/io.c
OBJ = $(SRC:.c=.o)

# Output executable name
EXEC = my_program

# Rule to link object files to create the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Rule to compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(EXEC)

# Install rule (optional)
install:
	cp $(EXEC) /usr/local/bin/
