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
  bool isStatement(const TOKEN lex) {
    return lex.token == ID || lex.token == IF_KEYWORD ||
    lex.token == PRINT_KEYWORD || lex.token == REPEAT_KEYWORD ||
    lex.token == WHILE_KEYWORD;
  }

  bool assertToken(const token_type expectedCode, Parser* parser) {
    TOKEN token = parser->getToken();
    if (token.token == expectedCode) return true;
    else {
      parser->print_err_pos();
      std::cout << "Unexpected token. Expected \"" << expectedCode << "\"\n";
    }
    return false;
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
      // Get first token
      source_line_n = lexicalAnalyzer->getLine();
      source_col_n = lexicalAnalyzer->getCol();
      current = lexicalAnalyzer->lex();

      // Run parse program
      if (parse_prgm()) {
        std::cout << "SUCCESS!!! File Pos: " << file_pos << '\n';
        outputFile->close();
        return true;
      } else {
        print_err_pos();
        std::cout << "Parsing Error" << '\n';
      }
    } else {
      std::cout << "ERROR: File iS NOT found" << '\n';
    }
    return false;
  }

  bool Parser::eof() {
    return lexicalAnalyzer->eof();
  }

  bool Parser::parse_prgm() {
    std::cout << "Let\'s Begin!" << '\n';

    if (!assertToken(FUNCTION_KEYWORD, this)) return false;
    if (!assertToken(ID, this)) return false;
    if (!assertToken(LEFT_PAREN_TOKEN, this)) return false;
    if (!assertToken(RIGHT_PAREN_TOKEN, this)) return false;

    if (!parse_block()) return false;

    if (!assertToken(END_KEYWORD, this)) return false;

    std::cout << "LINE "  << file_pos << ": " << "HALT" << '\n';
    file_pos++;

    return true;
  }

  bool Parser::parse_block() {
    TOKEN next;

    if (!parse_statement()) return false;

    next = nextToken();
    if (isStatement(next)) if (!parse_block()) return false;

    return true;
  }

  bool Parser::parse_statement() {
    TOKEN next = nextToken();
    if (next.token == ID) return parse_assignment_stmt();
    else if (next.token == IF_KEYWORD) return parse_if_stmt();
    else if (next.token == PRINT_KEYWORD) return parse_print_stmt();
    else if (next.token == WHILE_KEYWORD) return parse_while_stmt();
    else if (next.token == REPEAT_KEYWORD) return parse_repeat_stmt();
    else if (next.token == END_KEYWORD) return true;
    else return false;
  }

  bool Parser::parse_assignment_stmt() {
    TOKEN id = getToken();
    if (id.token != ID) {
      std::cout << "Unexpected token. Expected an ID, but received a\"" << id.token << "\"." << '\n';
      return false;
    }
    std::cout << "LINE "  << file_pos << ": " << "PUSH " << id.lex << '\n';
    file_pos++;

    if (!assertToken(ASSIGNMENT_OPERATOR, this)) return false;

    if (!arithmetic_expression()) return false;

    std::cout << "LINE "  << file_pos << ": " << "ASSIGN OP" << '\n';
    file_pos++;
    return true;
  }

  bool Parser::parse_if_stmt() {
    if (!assertToken(IF_KEYWORD, this)) return false;

    if (!boolean_expression()) return false;

    if (!assertToken(THEN_KEYWORD, this)) return false;

    int cond = file_pos;
    std::cout << "LINE "  << file_pos << ": " << "GOFALSE " << "LATER" << '\n';
    file_pos++;

    if (!parse_block()) return false;

    //int jmp1 = file_pos;
    std::cout << "LINE "  << file_pos << ": " << "GOTO " << "END" << '\n';
    file_pos++;

    if (!assertToken(ELSE_KEYWORD, this)) return false;

    if (!parse_block()) return false;

    int jmp2 = file_pos;
    std::cout << "LINE "  << file_pos << ": " << "GOTO " << 0 << '\n';
    file_pos++;

    if (!assertToken(END_KEYWORD, this)) return false;

    std::cout << "<<< On line " << cond << " GOFALSE "
      << jmp2-cond << " >>>\n";

    return true;
  }

  bool Parser::parse_while_stmt() {
    if (!assertToken(WHILE_KEYWORD, this)) return false;
    int begin = file_pos;

    if (!boolean_expression()) return false;

    if (!assertToken(DO_KEYWORD, this)) return false;

    int cond = file_pos;
    std::cout << "LINE "  << file_pos << ": " << "GOFALSE " << "LATER" << '\n';
    file_pos++;

    if (!parse_block()) return false;

    if (!assertToken(END_KEYWORD, this)) return false;

    std::cout << "LINE "  << file_pos << ": " << "GOTO " << file_pos-begin << '\n';
    file_pos++;

    std::cout << "\tLINE " << file_pos << ": On line " << cond << " GOFALSE " << file_pos-begin << '\n';

    return true;
  }

  bool Parser::parse_repeat_stmt() {
    if (!assertToken(REPEAT_KEYWORD, this)) return false;
    int begin = file_pos;

    if (!parse_block()) return false;

    if (!assertToken(UNTIL_KEYWORD, this)) return false;

    if (!boolean_expression()) return false;

    std::cout << "LINE "  << file_pos << ": " << "GOFALSE -" << file_pos-begin+1 << '\n';
    file_pos++;

    return true;
  }

  bool Parser::parse_print_stmt() {
    if (!assertToken(PRINT_KEYWORD, this)) return false;
    if (!assertToken(LEFT_PAREN_TOKEN, this)) return false;

    if (!arithmetic_expression()) return false;

    if (!assertToken(RIGHT_PAREN_TOKEN, this)) return false;

    std::cout << "LINE "  << file_pos << ": " << "PRINT" << '\n';
    file_pos++;

    return true;
  }

  bool Parser::boolean_expression() {
    if (!arithmetic_expression()) return false;

    TOKEN op = getToken();

    if (!arithmetic_expression()) return false;

    if (!relative_op(op)) return false;
    return true;
  }

  bool Parser::relative_op(const TOKEN op) {
    if (op.token == LE_OPERATOR) {
      std::cout << "LINE " << file_pos << ": " << "<= OP" << '\n';
      file_pos++;
    } else if (op.token == LT_OPERATOR) {
      std::cout << "LINE " << file_pos << ": " << "< OP" << '\n';
      file_pos++;
    } else if (op.token == GE_OPERATOR) {
      std::cout << "LINE " << file_pos << ": " << ">= OP" << '\n';
      file_pos++;
    } else if (op.token == GT_OPERATOR) {
      std::cout << "LINE " << file_pos << ": " << "> OP" << '\n';
      file_pos++;
    } else if (op.token == EQ_OPERATOR) {
      std::cout << "LINE " << file_pos << ": " << "== OPP" << '\n';
      file_pos++;
    } else if (op.token == NE_OPERATOR) {
      std::cout << "LINE " << file_pos << ": " << "!= OPP" << '\n';
      file_pos++;
    } else {
      print_err_pos();
      std::cout << "Invalid boolean operator." << '\n';
      return false;
    }
    return true;
  }

  bool Parser::arithmetic_expression() {
    TOKEN first_expr = getToken();
    std::cout << "TOKEN: " << first_expr.token << '\n';
    std::cout << "LEX: " << first_expr.lex << '\n';
    if (first_expr.token != ID && first_expr.token != LITERAL_INTEGER) {
      print_err_pos();
      std::cout << "Unexpected token. Expected an ID or Integer." << '\n';
      return false;
    }
    std::cout << "LINE " << file_pos << ": " << "PUSH " << first_expr.lex << '\n';
    file_pos++;
    // peek token
    TOKEN next = nextToken();
    if (next.token == ADD_OPERATOR || next.token == SUB_OPERATOR ||
        next.token == MULT_OPERATOR || next.token == DIV_OPERATOR) {
          TOKEN op = getToken();
          if (!arithmetic_expression()) return false;
          if (!arithmetic_op(op)) return false;
    }
    return true;
  }

  bool Parser::arithmetic_op(const TOKEN op) {
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
      print_err_pos();
      std::cout << "Invalid boolean operator." << '\n';
      return false;
    }
    return true;
  }

  void Parser::print_err_pos() const {
    std::cout << "ERROR:" << source_line_n << ":" <<
      source_col_n+1 << ": ";
  }

  TOKEN Parser::getToken() {
    TOKEN temp = current;
    source_line_n = lexicalAnalyzer->getLine();
    source_col_n = lexicalAnalyzer->getCol();
    current = lexicalAnalyzer->lex();
    return temp;
  }

  TOKEN Parser::nextToken() {
    return current;
  }

  void Parser::addInstruction(token_type instr=0, token_type val_t=0,
    int val=0) {

      instr -= PUSH_OPP;
      *outputFile << instr << ' ';

      switch (val_t) {
        case 0:
          *outputFile << 0 << ' ';;
          break;
        case ID:
          *outputFile << 3 << ' ';;
          break;
        case LITERAL_INTEGER:
          *outputFile << 2 << ' ';;
          break;
        default:
          print_err_pos();
          std::cout << "Incorrect type code" << '\n';
      }

      *outputFile << val;

      *outputFile << '\n';
  }

};
