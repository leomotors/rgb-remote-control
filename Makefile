# Compiler
CC := gcc

# Directories
SRC_DIR := src
BIN_DIR := bin
OUT_DIR := out

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

# Compiler flags
CFLAGS := -std=c17 -Wall -Wextra -O3 -lcurl -ljson-c

# Target
TARGET := rgb-remote

# Default target
all: $(TARGET)

# Rule to compile object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link the target
$(TARGET): $(OBJS)
	mkdir -p $(OUT_DIR)
	$(CC) $^ -o $(OUT_DIR)/$(TARGET) $(CFLAGS)

# Clean rule
clean:
	rm -rf $(BIN_DIR)/*.o $(OUT_DIR)/$(TARGET)

.PHONY: all clean
