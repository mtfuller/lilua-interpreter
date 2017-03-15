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

#include "Parser.h"

namespace lilua_interpreter_project {
  Parser::Parser(const char *source_file, const char *output_file) {
    lexicalAnalyzer = new Parser(source_file);
    outputFile = new std::ofstream(output_file);
  }

  Parser::~Parser() {
    delete lexicalAnalyzer;
    delete outputFile;
  }

  bool Parser::parse() {
    // See if source file exists

    // Run parse program
  }

  bool Parser::parse_prgm() {
    current_token = lexicalAnalyzer->lex();
    if (current_token != FUNCTION_KEYWORD) return false;
    current_token = lexicalAnalyzer->lex();
    if (current_token != ID) return false;
    current_token = lexicalAnalyzer->lex();
    if (current_token != LEFT_PAREN_TOKEN) return false;
    current_token = lexicalAnalyzer->lex();
    if (current_token != RIGHT_PAREN_TOKEN) return false;
    if (!parse_block()) return false;
    current_token = lexicalAnalyzer->lex();
    if (current_token != END_KEYWORD) return false;
  }

  bool Parser::parse_block() {

  }

  bool Parser::parse_statement() {

  }

  bool Parser::parse_assignment_stmt() {
    id = lexicalAnalyzer->lex();
    op = lexicalAnalyzer->lex();
    if (op != ASSIGNMENT_OPERATOR) return false;
    arithemetic_expression();
    return 0;
  }

  bool Parser::parse_if_stmt() {

  }

  bool Parser::parse_while_stmt() {

  }

  bool Parser::parse_repeat_stmt() {

  }

  bool Parser::parse_print_stmt() {

  }

  bool Parser::boolean_expression() {

  }

  bool Parser::relative_op() {

  }

  bool Parser::arithemetic_expression() {

  }

  bool Parser::arithemetic_op() {

  }
};
