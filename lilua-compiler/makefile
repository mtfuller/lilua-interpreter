# ------------------------------------------------------------------------------
# Makefile
# ------------------------------------------------------------------------------
CC 								= g++
CFLAGS 						= -g -Wall
INC_SCANNER				= -Isrc/Scanner

SOURCE_DIR 				= src
SOURCE_BUILD_DIR	= build/src
SCANNER_CPP				= $(SOURCE_DIR)/Scanner/Scanner.cpp

TEST_DIR 					= test
TEST_SCANNER			= $(TEST_DIR)/scanner_test.cpp
TEST_BUILD_DIR		= build/test

TEST							= scanner_test
TEST_EXES					= $(patsubst %,$(TEST_BUILD_DIR)/%.exe,$(TEST))
# ------------------------------------------------------------------------------

all:
	echo $(TEST_OBJS)
	mkdir build/test
	g++ -c test/scanner_test.cpp -o build/test/scanner_test.o

test: $(TEST_EXES)
	@echo "======================================================================"
	@echo "                            START TEST"
	@echo "======================================================================"
	@$(TEST_BUILD_DIR)/scanner_test.exe

$(TEST_BUILD_DIR)/scanner_test.exe: $(TEST_SCANNER) $(SCANNER_CPP)
	$(CC) $(CFLAGS) $(INC_SCANNER) -o $@ $^

clean:
	rm $(TEST_BUILD_DIR)/*.o

.PHONY: all test clean
