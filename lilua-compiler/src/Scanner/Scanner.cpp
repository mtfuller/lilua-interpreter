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
  Scanner::Scanner(char *file) {
    sourceFile = new std::ifstream(file);
    if (sourceFile->fail()) {
      std::cout << "Failed to open file..." << '\n';
      sourceFile->clear();
    }
    err_flag = false;
    current_token = UNKNOWN_TOKEN;
  }

  Scanner::~Scanner() {
    delete sourceFile;
  }

  LEXEME Scanner::lex() {
    char c;
    if (!sourceFile->get(c)) {
      sourceFile->close();
      LEXEME test = {EOF_TOKEN, c};
      return test;
    }
    LEXEME test = {UNKNOWN_TOKEN, c};
    return test;
  }

  char Scanner::getChar() {
    char b = 'b';
    return b;
  }
};
