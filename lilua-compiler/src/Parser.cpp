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

#include <iostream>
#include "Parser.h"

namespace lilua_interpreter_project {
  bool isStatement(TOKEN lex) {
    return lex.token == ID || lex.token == IF_KEYWORD ||
    lex.token == PRINT_KEYWORD || lex.token == REPEAT_KEYWORD ||
    lex.token == WHILE_KEYWORD;
  }

  Parser::Parser(const char *source_file, const char *output_file) {
    lexicalAnalyzer = new Scanner(source_file);
    outputFile = new std::ofstream(output_file);
    size_of_block = 0;
    file_pos = 0;
  }

  Parser::~Parser() {
    delete lexicalAnalyzer;
    delete outputFile;
  }

  bool Parser::parse() {
    // See if source file exists
    if (lexicalAnalyzer->is_file_found()) {
      // Run parse program
      if (parse_prgm()) {
        std::cout << "SUCCESS!!! File Pos: " << file_pos << '\n';
        return true;
      } else {
        std::cout << "ERROR:" << lexicalAnalyzer->getLine() << ":" <<
          lexicalAnalyzer->getCol() << ": Parsing Error" << '\n';
      }
    } else {
      std::cout << "ERROR: File iS NOT found" << '\n';
    }
    return false;
  }

  bool Parser::parse_prgm() {
    std::cout << "Let\'s Begin!" << '\n';
    current = lexicalAnalyzer->lex();
    if (current.token != FUNCTION_KEYWORD) return false;
    current = lexicalAnalyzer->lex();
    if (current.token != ID) return false;
    current = lexicalAnalyzer->lex();
    if (current.token != LEFT_PAREN_TOKEN) return false;
    current = lexicalAnalyzer->lex();
    if (current.token != RIGHT_PAREN_TOKEN) return false;

    if (!parse_block()) return false;

    current = lexicalAnalyzer->lex();
    if (current.token != END_KEYWORD) return false;

    std::cout << "LINE "  << file_pos << ": " << "HALT" << '\n';
    file_pos++;

    return true;
  }

  bool Parser::parse_block() {
    TOKEN next;
    size_of_block = 0;
    do {
      size_of_block++;
      if (!parse_statement()) return false;
      next = lexicalAnalyzer->peekLex();
    } while (isStatement(next));
    return true;
  }

  bool Parser::parse_statement() {
    TOKEN next = lexicalAnalyzer->peekLex();
    if (next.token == ID) {
      return parse_assignment_stmt();
    } else if (next.token == IF_KEYWORD) {
      return parse_if_stmt();
    } else if (next.token == PRINT_KEYWORD) {
      return parse_print_stmt();
    } else if (next.token == WHILE_KEYWORD) {
      return parse_while_stmt();
    } else if (next.token == REPEAT_KEYWORD) {
      return parse_repeat_stmt();
    } else if (next.token == END_KEYWORD) {
      return true;
    } else {
      return false;
    }
  }

  bool Parser::parse_assignment_stmt() {
    TOKEN id = lexicalAnalyzer->lex();
    if (id.token != ID) return false;
    std::cout << "LINE "  << file_pos << ": " << "PUSH " << id.lex << '\n';
    file_pos++;

    TOKEN op = lexicalAnalyzer->lex();
    if (op.token != ASSIGNMENT_OPERATOR) return false;

    arithemetic_expression();

    std::cout << "LINE "  << file_pos << ": " << "ASSIGN OP" << '\n';
    file_pos++;
    return true;
  }

  bool Parser::parse_if_stmt() {
    current = lexicalAnalyzer->lex();
    if (current.token != IF_KEYWORD) return false;

    if (!boolean_expression()) return false;

    current = lexicalAnalyzer->lex();
    if (current.token != THEN_KEYWORD) return false;

    size_t cond = file_pos;
    std::cout << "LINE "  << file_pos << ": " << "GOFALSE " << "LATER" << '\n';
    file_pos++;

    if (!parse_block()) return false;

    size_t jmp1 = file_pos;
    std::cout << "LINE "  << file_pos << ": " << "GOTO " << "END" << '\n';
    file_pos++;

    current = lexicalAnalyzer->lex();
    if (current.token != ELSE_KEYWORD) return false;

    if (!parse_block()) return false;

    size_t jmp2 = file_pos;
    std::cout << "LINE "  << file_pos << ": " << "GOTO " << 0 << '\n';
    file_pos++;

    current = lexicalAnalyzer->lex();
    if (current.token != END_KEYWORD) return false;

    std::cout << "<<< On line " << cond << " GOFALSE "
      << jmp2-cond << " >>>\n";

    return true;
  }

  bool Parser::parse_while_stmt() {
    current = lexicalAnalyzer->lex();
    if (current.token != WHILE_KEYWORD) return false;
    size_t begin = file_pos;

    if (!boolean_expression()) return false;

    current = lexicalAnalyzer->lex();
    if (current.token != DO_KEYWORD) return false;

    size_t cond = file_pos;
    std::cout << "LINE "  << file_pos << ": " << "GOFALSE " << "LATER" << '\n';
    file_pos++;

    if (!parse_block()) return false;

    current = lexicalAnalyzer->lex();
    if (current.token != END_KEYWORD) return false;

    std::cout << "LINE "  << file_pos << ": " << "GOTO " << file_pos-begin << '\n';
    file_pos++;

    std::cout << "\tLINE " << file_pos << ": On line " << cond << " GOFALSE " << file_pos-begin << '\n';

    return true;
  }

  bool Parser::parse_repeat_stmt() {
    current = lexicalAnalyzer->lex();
    if (current.token != REPEAT_KEYWORD) return false;
    size_t begin = file_pos;

    if (!parse_block()) return false;

    current = lexicalAnalyzer->lex();
    if (current.token != UNTIL_KEYWORD) return false;

    if (!boolean_expression()) return false;

    std::cout << "LINE "  << file_pos << ": " << "GOFALSE -" << file_pos-begin+1 << '\n';
    file_pos++;

    return true;
  }

  bool Parser::parse_print_stmt() {
    current = lexicalAnalyzer->lex();
    if (current.token != PRINT_KEYWORD) return false;
    current = lexicalAnalyzer->lex();
    if (current.token != LEFT_PAREN_TOKEN) return false;

    if (!arithemetic_expression()) return false;

    current = lexicalAnalyzer->lex();
    if (current.token != RIGHT_PAREN_TOKEN) return false;

    std::cout << "LINE "  << file_pos << ": " << "PRINT" << '\n';
    file_pos++;

    return true;
  }

  bool Parser::boolean_expression() {
    current = lexicalAnalyzer->lex();
    std::cout << "LINE "  << file_pos << ": " << "PUSH " << current.lex << '\n';
    file_pos++;
    TOKEN op = lexicalAnalyzer->lex();
    current = lexicalAnalyzer->lex();
    std::cout << "LINE "  << file_pos << ": " << "PUSH " << current.lex << '\n';
    file_pos++;
    if (!relative_op(op)) return false;
    return true;
  }

  bool Parser::relative_op(TOKEN op) {
    if (op.token == LE_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << "<= OP" << '\n';
      file_pos++;
    } else if (op.token == LT_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << "< OP" << '\n';
      file_pos++;
    } else if (op.token == GE_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << ">= OP" << '\n';
      file_pos++;
    } else if (op.token == GT_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << "> OP" << '\n';
      file_pos++;
    } else if (op.token == EQ_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << "== OPP" << '\n';
      file_pos++;
    } else if (op.token == NE_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << "!= OPP" << '\n';
      file_pos++;
    } else {
      return false;
    }
    return true;
  }

  bool Parser::arithemetic_expression() {
    TOKEN next;
    current = lexicalAnalyzer->lex();
    if (current.token != ID && current.token != LITERAL_INTEGER)
      return false;
    std::cout << "LINE "  << file_pos << ": " << "PUSH " << current.lex << '\n';
    file_pos++;
    // peek token
    next = lexicalAnalyzer->peekLex();
    if (next.token == ADD_OPERATOR || next.token == SUB_OPERATOR ||
        next.token == MULT_OPERATOR || next.token == DIV_OPERATOR) {
          TOKEN op = lexicalAnalyzer->lex();
          if (!arithemetic_expression()) return false;
          if (!arithemetic_op(op)) return false;
    }
    return true;
  }

  bool Parser::arithemetic_op(TOKEN op) {
    if (op.token == ADD_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << "ADD OP" << '\n';
      file_pos++;
    } else if(op.token == SUB_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << "SUB OP" << '\n';
      file_pos++;
    } else if(op.token == MULT_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << "MULT OP" << '\n';
      file_pos++;
    } else if(op.token == DIV_OPERATOR) {
      std::cout << "LINE "  << file_pos << ": " << "DIV OP" << '\n';
      file_pos++;
    } else {
      return false;
    }
    return true;
  }


};
