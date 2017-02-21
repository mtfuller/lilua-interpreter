// =============================================================================
// Author(s): Thomas Fuller
// Project:   Module 3 - 1st Deliverable
// File:      scanner_test.cpp
// =============================================================================
// Description:
//
// =============================================================================

#include <iostream>
//#include <ifstream>
#include <cstring>
#include <cassert>
#include "Scanner.h"

using namespace lilua_interpreter_project;

bool lexeme_comp(LEXEME actual, LEXEME expected) {
    if (actual.token == expected.token) {
        return true;
    } else {
        std::cout << "Failed... The expected token was: "<< expected.token << ".\n" <<
        "The actual token was: " << actual.token << '\n';
        return false;
    }
}

int main() {
    std::cout << "Keyword Binary Search Test" << '\n';
    int val;
    std::cout << "Searching for the keyword \"repeat\"...";
    val = keyword_bin_search("repeat");
    if (val == REPEAT_KEYWORD) {
        std::cout << "SUCCESS!!!" << '\n';
    } else {
        std::cout << "failed. It returned: " << val << '\n';
    }/*
    std::cout << "Searching for the keyword \"do\"...";
    val = keyword_bin_search("do");
    if (val == DO_KEYWORD) {
        std::cout << "SUCCESS!!!" << '\n';
    } else {
        std::cout << "failed. It returned: " << val << '\n';
    }
    std::cout << "Searching for the keyword \"while\"...";
    val = keyword_bin_search("while");
    if (val == WHILE_KEYWORD) {
        std::cout << "SUCCESS!!!" << '\n';
    } else {
        std::cout << "failed. It returned: " << val << '\n';
    }
    std::cout << "Searching for the non-existent keyword \"notinthetable\"...";
    val = keyword_bin_search("notinthetable");
    if (val == -1) {
        std::cout << "SUCCESS!!!" << '\n';
    } else {
        std::cout << "failed. It returned: " << val << '\n';
    }
*/
    std::cout << "\nScanner Test #1" << '\n';
  char simple[] = "build/test/res/simple.lua";
      std::cout << "Testing scanner with the file: \"" << simple << "\"...";
  Scanner myScanner(simple);
  size_t index = 0;
  const LEXEME ans1[] = {
      {FUNCTION_KEYWORD,"function"},
      {ID,"f"},
      {UNKNOWN_TOKEN,"("},
      {UNKNOWN_TOKEN,")"},
      {ID,"a"},
      {ASSIGNMENT_OPERATOR,"="},
      {LITERAL_INTEGER,"7"},
      {PRINT_KEYWORD,"print"},
      {UNKNOWN_TOKEN,"("},
      {ID,"a"},
      {UNKNOWN_TOKEN,")"},
      {ID,"b"},
      {ASSIGNMENT_OPERATOR,"="},
      {LITERAL_INTEGER,"8"},
      {PRINT_KEYWORD,"print"},
      {UNKNOWN_TOKEN,"("},
      {ID,"b"},
      {UNKNOWN_TOKEN,")"},
      {ID,"c"},
      {ASSIGNMENT_OPERATOR,"="},
      {ID,"a"},
      {MULT_OPERATOR,"*"},
      {ID,"b"},
      {PRINT_KEYWORD,"print"},
      {UNKNOWN_TOKEN,"("},
      {ID,"c"},
      {UNKNOWN_TOKEN,")"},
      {END_KEYWORD,"end"},
      {EOF_TOKEN,""}
  };

  LEXEME test;
  do {
    test = myScanner.lex();
    if (!lexeme_comp(test, ans1[index++])) return -1;
  } while (test.token != -1);
  std::cout << "SUCCESS!!!" << '\n';
  return 0;
}
