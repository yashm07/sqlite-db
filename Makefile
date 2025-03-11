SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
TEST_DIR := tests

CC := gcc
CFLAGS := -Wall -I$(INCLUDE_DIR)
LDFLAGS := -lcmocka

# Source files (main program)
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Object files for main program
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Test source files
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)

# Object files for tests
TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target location for main program and test executable
TARGET := $(BUILD_DIR)/db_sqlite
TEST_TARGET := $(BUILD_DIR)/test_io

# Default target (build main program)
all: $(TARGET)

# Rule to build the main program
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule to build the test executable
$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CC) $(OBJS) $(TEST_OBJS) -o $(TEST_TARGET) $(LDFLAGS)

# Rule to build object files for the main program
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)  # Ensure the build directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object files for the tests
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)  # Ensure the build directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Clean command to remove build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
