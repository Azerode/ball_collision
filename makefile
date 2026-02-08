# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -D_DEFAULT_SOURCE -Wno-missing-braces -g
# Raylib flags for Mac (Homebrew or default install)
# You might need to adjust paths depending on where raylib is installed
LDFLAGS = -L/opt/homebrew/lib -L/usr/local/lib -lraylib -framework OpenGL -framework IOKit -framework Cocoa
INCLUDES = -I/opt/homebrew/include -I/usr/local/include

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files (recursive search)
SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/collision

# Main target
all: $(TARGET)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link object files to create executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the game
run: all
	./$(TARGET)

.PHONY: all clean run
