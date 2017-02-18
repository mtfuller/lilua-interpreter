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
#include "Scanner.h"

using namespace lilua_interpreter_project;

int main() {
  char simple[] = "build/test/res/simple.lua";
  Scanner myScanner(simple);
  LEXEME test;
  do {
    test = myScanner.lex();
    std::cout << "LEXEME:" << std::endl;
    std::cout << "TOKEN CODE:\t" << test.token << '\n';
    std::cout << "CHARACTERS:\t" << test.lex << '\n';
  } while (test.token != -1);
  return 0;
}
