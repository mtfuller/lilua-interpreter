// =============================================================================
// Author(s): Thomas Fuller
// Project:   Module 5 - 2nd Deliverable
// File:      parser_test.cpp
// =============================================================================
// Description:
//
// =============================================================================

#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "Parser.h"

using namespace lilua_interpreter_project;

struct INSTRUCTION {
  int op;
  int type;
  int val;
};

int bytes_to_int(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4) {
  int result = 0;

  result = (b4<<24) | (b3<<16) | (b2<<8) | (b1);

  return (int) result;
}

bool parserTest(const char* sourceFile, const char* outputFile, const INSTRUCTION ans[], size_t n) {
  std::cout << "Parser Test for " << sourceFile << '\n';

  // Run parser for specific file
  Parser testParser(sourceFile, outputFile);
  testParser.parse();

  std::ifstream resultFile(outputFile, std::ios::binary);

  char input;

  std::vector<unsigned char> resultVector;

  while (resultFile.read(&input, 1))
  {
      unsigned char test = (unsigned char) input;
      resultVector.push_back(test);
  }

  size_t ans_i = 0;

  for (std::vector<unsigned char>::iterator it = resultVector.begin(); it < resultVector.end(); ++it) {
    if (ans_i > n-1) {
      std::cout << "AT INDEX:" << ans_i << " - ";
      std::cout << "PARSER FOUND TOO MANY TOKENS!" << '\n';
      return false;
    }

    int action = (int) *it;
    ++it;
    int type = (int) *it;
    ++it;
    unsigned char b1 = *it;
    ++it;
    unsigned char b2 = *it;
    ++it;
    unsigned char b3 = *it;
    ++it;
    unsigned char b4 = *it;
    int val = bytes_to_int(b1,b2,b3,b4);

    INSTRUCTION test = ans[ans_i];

    if (action != test.op-PUSH_OP) {
      std::cout << "AT INDEX:" << ans_i+1 << " - ";
      std::cout << "OP IS NOT CORRECT. Expected " << test.op-PUSH_OP << ", but found " << action << '\n';
      return false;
    }

    if (type != test.type) {
      std::cout << "AT INDEX:" << ans_i+1 << " - ";
      std::cout << "TYPE IS NOT CORRECT. Expected " << test.type << ", but found " << type << '\n';
      return false;
    }

    if (val != test.val) {
      std::cout << "AT INDEX:" << ans_i+1 << " - ";
      std::cout << "VALUE IS NOT CORRECT. Expected " << test.val << ", but found " << val << '\n';
      return false;
    }

    ++ans_i;
  }

  if (resultVector.size()/6 > n) {
    std::cout << "AT INDEX:" << ans_i << " - ";
    std::cout << "PARSER FOUND TOO FEW TOKENS!" << '\n';
    return false;
  }

  std::cout << "TEST WAS SUCCESSFUL!!!" << "\n\n";

  resultFile.close();

  //if (remove(outputFile) != 0) perror( "Error deleting file" );
  //else puts( "File successfully deleted" );

  return true;
}

bool test1() {
  INSTRUCTION ans[] = {
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 7},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 0},
    {PRINT_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 8},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {PRINT_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {MULT_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 2},
    {PRINT_OP, NONE_TYPE, 0},
    {HALT_OP, NONE_TYPE, 0}
  };
  return parserTest("build/test/res/simple.lua","build/test/output.lil",ans,18);
}

bool test2() {
  INSTRUCTION ans[] = {
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 7},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 0},
    {PRINT_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 8},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {PRINT_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {MULT_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 2},
    {PRINT_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 3},
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {DIV_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 4},
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {ADD_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 5},
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {SUB_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 3},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 1},
    {GT_OP, NONE_TYPE, 0},
    {GOFALSE_OP, LITERAL_INTEGER_TYPE, 3},
    {PUSH_OP, ID_TYPE, 3},
    {PRINT_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 3},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {PRINT_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 0},
    {PUSH_OP, ID_TYPE, 5},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {LT_OP, NONE_TYPE, 0},
    {GOFALSE_OP, LITERAL_INTEGER_TYPE, 3},
    {PUSH_OP, ID_TYPE, 5},
    {PRINT_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 3},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {PRINT_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 0},
    {PUSH_OP, ID_TYPE, 4},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 15},
    {LE_OP, NONE_TYPE, 0},
    {GOFALSE_OP, LITERAL_INTEGER_TYPE, 3},
    {PUSH_OP, ID_TYPE, 4},
    {PRINT_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 3},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {PRINT_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 0},
    {HALT_OP, NONE_TYPE, 0}
  };
  return parserTest("build/test/res/comparison.lua","build/test/comparison.lil",ans,63);
}

bool test3() {
  INSTRUCTION ans[] = {
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 100},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 1},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 17},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 2},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 2},
    {DIV_OP, NONE_TYPE, 0},
    {MULT_OP, NONE_TYPE, 0},
    {SUB_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 17},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {EQ_OP, NONE_TYPE, 0},
    {GOFALSE_OP, LITERAL_INTEGER_TYPE, 8},
    {PUSH_OP, ID_TYPE, 2},
    {PRINT_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 1},
    {ADD_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 6},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 1},
    {ADD_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 0},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, ID_TYPE, 13},
    {GT_OP, NONE_TYPE, 0},
    {GOFALSE_OP, LITERAL_INTEGER_TYPE, -31},
    {HALT_OP, NONE_TYPE, 0}
  };
  return parserTest("build/test/res/even-nums.lua","build/test/even-nums.lil",ans,38);
}

bool test4() {
  INSTRUCTION ans[] = {
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 8},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {GT_OP, NONE_TYPE, 0},
    {GOFALSE_OP, LITERAL_INTEGER_TYPE, 64},
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 1},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 0},
    {PRINT_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 1},
    {EQ_OP, NONE_TYPE, 0},
    {GOFALSE_OP, LITERAL_INTEGER_TYPE, 6},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 1},
    {SUB_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 45},
    {PUSH_OP, ID_TYPE, 1},
    {PRINT_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 2},
    {EQ_OP, NONE_TYPE, 0},
    {GOFALSE_OP, LITERAL_INTEGER_TYPE, 6},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 1},
    {SUB_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 32},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 2},
    {SUB_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {GT_OP, NONE_TYPE, 0},
    {GOFALSE_OP, LITERAL_INTEGER_TYPE, 19},
    {PUSH_OP, ID_TYPE, 2},
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {ADD_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {ASSIGN_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 1},
    {PUSH_OP, ID_TYPE, 2},
    {ASSIGN_OP, NONE_TYPE, 0},
  	{PUSH_OP, ID_TYPE, 2},
  	{PRINT_OP, NONE_TYPE, 0},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, ID_TYPE, 13},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 1},
    {SUB_OP, NONE_TYPE, 0},
    {ASSIGN_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, -23},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 3},
    {PUSH_OP, LITERAL_INTEGER_TYPE, 0},
    {PRINT_OP, NONE_TYPE, 0},
    {GOTO_OP, LITERAL_INTEGER_TYPE, 0},
    {HALT_OP, NONE_TYPE, 0}
  };
  return parserTest("build/test/res/fibonacci.lua","build/test/fibonacci.lil",ans,75);
}

int main() {

  if (!test1()) return -1;
  if (!test2()) return -1;
  if (!test3()) return -1;
  if (!test4()) return -1;

  return 0;
}
