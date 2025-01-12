# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

# Target executable name
TARGET = txtmax

# Source files
SRC = txtmax9.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
