# ------------------------------------------------------------------------------
# Makefile
# ------------------------------------------------------------------------------
CC = g++
CFLAGS = -g -Wall
INC_SCANNER = -Isrc/Scanner

BUILD_DIR = build

SOURCE_DIR = src
SOURCE_BUILD_DIR = $(BUILD_DIR)/src
SCANNER_CPP = $(SOURCE_DIR)/Scanner/Scanner.cpp

TEST_DIR = test
TEST_RES = $(TEST_DIR)/res
TEST_SCANNER = $(TEST_DIR)/scanner_test.cpp
TEST_RES_FILES = $(wildcard $(TEST_RES)/*)

TEST_BUILD_DIR = $(BUILD_DIR)/test
TEST_BUILD_RES_DIR = $(TEST_BUILD_DIR)/res

TEST = scanner_test
TEST_BUILD_RES_FILES = $(patsubst %,$(TEST_BUILD_RES_DIR)/%,$(notdir $(TEST_RES_FILES)))
TEST_EXES = $(patsubst %,$(TEST_BUILD_DIR)/%.exe,$(TEST))

# ------------------------------------------------------------------------------

all:
	mkdir build/test
	g++ -c test/scanner_test.cpp -o build/test/scanner_test.o

test: $(TEST_BUILD_DIR) $(TEST_BUILD_RES_FILES) $(TEST_EXES)
	@echo "===================================================================="
	@echo "                          START TEST"
	@echo "===================================================================="
	@$(TEST_BUILD_DIR)/scanner_test.exe

$(TEST_BUILD_RES_DIR)/%: $(TEST_RES)/% $(TEST_BUILD_RES_DIR)
	@cp $< $(dir $@)

$(TEST_BUILD_DIR)/scanner_test.exe: $(TEST_SCANNER) $(SCANNER_CPP)
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

.PHONY: all test clean
