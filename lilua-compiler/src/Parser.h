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
#include "Scanner.h"
#include "lilua_symbol.h"         // Symbol definitions

namespace lilua_interpreter_project {

  bool isStatement(TOKEN lex);

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
    bool relative_op(TOKEN op);
    bool arithemetic_expression();
    bool arithemetic_op(TOKEN op);
    //void addInstruction(BYTE instr_code, token_type value_type, int value);
    TOKEN current;
    Scanner* lexicalAnalyzer;
    std::ofstream* outputFile;
    size_t size_of_block;
    size_t file_pos;
  };

};

#endif
