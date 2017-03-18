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
    TOKEN getToken();
    TOKEN nextToken();
    bool eof();
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
    void print_err_pos();

    void addInstruction(token_type instr, token_type val_t, int val);

    friend bool assertToken(token_type expectedCode, Parser* parser);

    TOKEN current;
    Scanner* lexicalAnalyzer;
    std::ofstream* outputFile;
    size_t size_of_block;
    size_t file_pos;
  };

};

#endif
