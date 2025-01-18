# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -O2

# Source and Output
SRC = txtmax.c
OBJ = txtmax.o
TARGET = txtmax

# Default Rule
all: $(TARGET)

# Compiling the source file into an object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

# Linking the object file to create the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets (to prevent conflicts with files named "all" or "clean")
.PHONY: all clean
