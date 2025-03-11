SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

CC := gcc
CFLAGS := -Wall -I$(INCLUDE_DIR)

# source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# object files
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# target location
TARGET := $(BUILD_DIR)/db_sqlite

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# move all build files into build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)  # Ensure the build directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# clean command
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
