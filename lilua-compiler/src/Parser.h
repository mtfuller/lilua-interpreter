// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 5 - 2nd Deliverable
// File:      Parser.h
// =============================================================================
// Description:
// This file is the header file of the Parser class. All function and data
// memebers are defined below.
// =============================================================================

#ifndef _LILUA_PARSER_H
#define _LILUA_PARSER_H

#include "Scanner.h"
#include "lilua_symbol.h"         // Symbol definitions

namespace lilua_interpreter_project {

  bool isStatement(const TOKEN lex);

  class Parser {
  public:
    Parser(const char *sourceFile, const char *outputFile);
    ~Parser();
    bool parse();
    bool eof();
  private:
    TOKEN getToken();
    TOKEN nextToken();

    bool parse_prgm();
    bool parse_block();
    bool parse_statement();
    bool parse_assignment_stmt();
    bool parse_if_stmt();
    bool parse_while_stmt();
    bool parse_repeat_stmt();
    bool parse_print_stmt();
    bool boolean_expression();
    bool relative_op(const TOKEN op);
    bool arithmetic_expression();
    bool arithmetic_op(const TOKEN op);

    void print_err_pos() const;
    void addInstruction(token_type instr, token_type val_t, int val);

    friend bool assertToken(const token_type expectedCode, Parser* parser);

    TOKEN current;
    Scanner* lexicalAnalyzer;
    std::ofstream* outputFile;
    size_t size_of_block;
    size_t file_pos;
    size_t source_line_n;
    size_t source_col_n;
  };

};

#endif
