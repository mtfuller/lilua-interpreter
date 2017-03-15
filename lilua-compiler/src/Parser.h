// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 3 - 1st Deliverable
// File:      Scanner.cpp
// =============================================================================
// Description:
// This file is the implementation of the scanner class.
// =============================================================================

#ifndef _LILUA_PARSER_H
#define _LILUA_PARSER_H

#include <fstream>                // Used for file input
#include "lilua_symbol.h"         // Symbol definitions

namespace lilua_interpreter_project {

  class Parser {
  public:
    Parser(const char *sourceFile, const char *outputFile);
    ~Parser();
    bool parse();
  private:
    bool parse_prgm();
    bool parse_block();
    bool parse_statement();
    bool parse_assignment_stmt();
    bool parse_if_stmt();
    bool parse_while_stmt();
    bool parse_repeat_stmt();
    bool parse_print_stmt();
    bool boolean_expression();
    bool relative_op();
    bool arithemetic_expression();
    bool arithemetic_op();
    TOKEN current_token;
    Scanner* lexicalAnalyzer;
    std::ofstream* outputFile;
  }

};

#endif
