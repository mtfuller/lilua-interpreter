// =============================================================================
// Author(s): Thomas Fuller
// Project:   Module 3 - 1st Deliverable
// File:      Scanner.cpp
// =============================================================================
// Description:
//
// =============================================================================
#include <iostream>
#include "Scanner.h"
#include "lilua_symbol.h"

namespace lilua_interpreter_project {
  Scanner::Scanner(std::ifstream& file) {
    sourceFile = &file;
    err_flag = false;
    current_token = UNKNOWN_TOKEN;
  }

  LEXEME Scanner::lex() {
    sourceFile.open("res/simple.lua");
    char c;
    while (sourceFile.get(c))
        std::cout << c << std::endl;
    LEXEME test = {UNKNOWN_TOKEN, "TEST"};
    return test;
  }

  char Scanner::getChar() {
      return
  }
};
