.PHONY: all clean expand help

CC = gcc
C_FLAGS = -Wall -g -Iinclude -O0
BUILD_DIR = build
EXAMPLES_DIR = examples
EXPAND_DIR = expanded

SRC_FILES = $(wildcard $(EXAMPLES_DIR)/*.c)
BINARIES = $(patsubst $(EXAMPLES_DIR)/%.c,$(BUILD_DIR)/%,$(SRC_FILES))
EXPANDED_FILES = $(patsubst $(EXAMPLES_DIR)/%.c,$(EXPAND_DIR)/%.i,$(SRC_FILES))

# Default target: build all individual binaries
all: $(BINARIES)

# Compile each .c to its own binary
$(BUILD_DIR)/%: $(EXAMPLES_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	$(CC) $(C_FLAGS) $< -o $@

# Expand all: preprocess each .c into its own .i
expand: $(EXPANDED_FILES)

$(EXPAND_DIR)/%.i: $(EXAMPLES_DIR)/%.c | $(EXPAND_DIR)
	@echo "Expanding $< -> $@"
	$(CC) $(C_FLAGS) -E $< -o $@

# Ensure build/ and expanded/ dirs exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXPAND_DIR):
	mkdir -p $(EXPAND_DIR)

clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR) $(EXPAND_DIR)

help:
	@echo "Available targets:"
	@echo "  all     - Compile all .c files into separate binaries"
	@echo "  expand  - Expand all .c files to .i (preprocessed)"
	@echo "  clean   - Remove build and expanded files"
	@echo "  help    - Show this help message"
