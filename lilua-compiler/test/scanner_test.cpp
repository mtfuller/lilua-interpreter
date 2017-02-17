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
  std::ifstream inputFile;
  Scanner myScanner(inputFile);
  LEXEME test = myScanner.lex();
  std::cout << "LEXEME:" << std::endl;
  std::cout << "TOKEN CODE:\t" << test.token << '\n';
  std::cout << "CHARACTERS:\t" << test.lex << '\n';
  return 0;
}
