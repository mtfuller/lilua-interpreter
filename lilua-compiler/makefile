# ------------------------------------------------------------------------------
# Makefile
# ------------------------------------------------------------------------------
CC = g++
CFLAGS = -g -Wall
INC_SCANNER = -Isrc/

BUILD_DIR = build

SOURCE_DIR = src
SOURCE_BUILD_DIR = $(BUILD_DIR)/src
SOURCE_CPP  = $(wildcard $(SOURCE_DIR)/*.cpp)

TEST_DIR = test
TEST_RES = $(TEST_DIR)/res
TEST_SCANNER = $(TEST_DIR)/scanner_test.cpp
TEST_PARSER = $(TEST_DIR)/parser_test.cpp
TEST_RES_FILES = $(wildcard $(TEST_RES)/*)

TEST_BUILD_DIR = $(BUILD_DIR)/test
TEST_BUILD_RES_DIR = $(TEST_BUILD_DIR)/res

TEST = scanner_test parser_test
TEST_BUILD_RES_FILES = $(patsubst %,$(TEST_BUILD_RES_DIR)/%,$(notdir $(TEST_RES_FILES)))
TEST_EXES = $(patsubst %,$(TEST_BUILD_DIR)/%.exe,$(TEST))

# ------------------------------------------------------------------------------

all: test app
	@echo "Finished!"

app: $(SOURCE_BUILD_DIR) $(SOURCE_CPP)
	@echo "Building $(notdir $@)..."
	@$(CC) $(CFLAGS) -o $(SOURCE_BUILD_DIR)/liluac $(SOURCE_CPP)

test: $(TEST_BUILD_DIR) $(TEST_BUILD_RES_FILES) $(TEST_EXES)
	@echo "===================================================================="
	@echo "                          START TEST"
	@echo "===================================================================="
	@$(TEST_BUILD_DIR)/scanner_test.exe
	@$(TEST_BUILD_DIR)/parser_test.exe

$(SOURCE_BUILD_DIR): $(BUILD_DIR)
	@rm -r -f $@
	@mkdir $@

$(TEST_BUILD_RES_DIR)/%: $(TEST_RES)/% $(TEST_BUILD_RES_DIR)
	@cp $< $(dir $@)

$(TEST_BUILD_DIR)/scanner_test.exe: $(TEST_SCANNER) $(SOURCE_DIR)/Scanner.cpp
	@echo "Building $(notdir $@)..."
	@$(CC) $(CFLAGS) $(INC_SCANNER) -o $@ $^

$(TEST_BUILD_DIR)/parser_test.exe: $(TEST_PARSER) $(SOURCE_DIR)/Parser.cpp $(SOURCE_DIR)/Scanner.cpp
	@echo "Building $(notdir $@)..."
	@$(CC) $(CFLAGS) $(INC_SCANNER) -o $@ $^

$(TEST_BUILD_RES_DIR): $(TEST_BUILD_DIR)
	@rm -r -f $@
	@mkdir $@

$(TEST_BUILD_DIR): $(BUILD_DIR)
	@rm -r -f $@
	@mkdir $@

$(BUILD_DIR):
	@rm -r -f $@
	@mkdir $@

clean:
	rm $(TEST_BUILD_DIR)/*.o

.PHONY: all app test clean
