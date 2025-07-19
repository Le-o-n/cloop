.PHONY: all clean expand

CC = gcc
C_FLAGS = -Wall -g -Iinclude
BUILD_DIR = build
SRC_DIR = src
TARGET = main
EXPAND_DIR = expanded

# List your source files here
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
EXPANDED_FILES = $(patsubst $(SRC_DIR)/%.c,$(EXPAND_DIR)/%.i,$(SRC_FILES))

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJ_FILES) | $(BUILD_DIR)
	@echo "Linking..."
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(C_FLAGS) -c $< -o $@

$(BUILD_DIR):
	@echo "Creating build dir"
	mkdir -p $(BUILD_DIR)

$(EXPAND_DIR):
	@echo "Creating expanded sources dir"
	mkdir -p $(EXPAND_DIR)

# Rule to expand macros
expand: $(EXPANDED_FILES) | $(EXPAND_DIR)

$(EXPAND_DIR)/%.i: $(SRC_DIR)/%.c | $(EXPAND_DIR)
	@echo "Expanding macros in $<..."
	$(CC) $(C_FLAGS) -E $< -o $@

clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR) $(EXPAND_DIR)

run: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET)