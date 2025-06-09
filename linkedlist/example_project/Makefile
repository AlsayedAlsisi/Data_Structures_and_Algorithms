# Makefile for LinkedList Project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = 

# Project name
TARGET = linkedlist_project

# Source files
SOURCES = array_test.c CustomArray.c linkedlist.c main.c

# Object files (replace .c with .o)
OBJECTS = $(SOURCES:.c=.o)

# Header files (for dependency tracking)
HEADERS = $(wildcard *.h)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Clean and rebuild
rebuild: clean all

# Install (optional - modify path as needed)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug with gdb
debug: $(TARGET)
	gdb ./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  clean    - Remove object files and executable"
	@echo "  rebuild  - Clean and build"
	@echo "  run      - Build and run the program"
	@echo "  debug    - Build and run with gdb debugger"
	@echo "  install  - Install executable to /usr/local/bin/"
	@echo "  help     - Show this help message"

# Phony targets (not actual files)
.PHONY: all clean rebuild install uninstall run debug help