// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 5 - 2nd Deliverable
// File:      Parser.cpp
// =============================================================================
// Description:
// This file is the implementation of the scanner class.
// =============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cctype>
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
    outputPath = new std::string(output_file);
    data = new std::vector<BYTE>;
    size_of_block = 0;
    file_pos = 0;
  }

  Parser::~Parser() {
    delete lexicalAnalyzer;
    delete outputFile;
    delete outputPath;
    delete data;
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
        outputFile = new std::ofstream(outputPath->c_str(), std::ios::binary);
        size_t size = data->size();
        size_t index = 0;
        char memdata[size];
        for (std::vector<BYTE>::iterator it = data->begin(); it != data->end(); ++it) {
          std::cout << "INSTR: " << (int) *it << ':';
          ++it;
          std::cout << (int) *it << ':';
          ++it;
          std::cout << (int) *it << ':';
          ++it;
          std::cout << (int) *it << ':';
          ++it;
          std::cout << (int) *it << ':';
          ++it;
          std::cout << (int) *it << '\n';
        }
        for (std::vector<BYTE>::iterator it = data->begin(); it != data->end(); ++it)
            memdata[index++] = (char) *it;
        outputFile->write(memdata,size);
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

    addInstruction(HALT_OP, NONE_TYPE, 0);
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

    int id_code = toupper(id.lex[0]) - 'A';
    addInstruction(PUSH_OP, id.token, id_code);
    file_pos++;

    if (!assertToken(ASSIGNMENT_OPERATOR, this)) return false;

    if (!arithmetic_expression()) return false;

    addInstruction(ASSIGN_OP, NONE_TYPE, 0);
    file_pos++;
    return true;
  }

  bool Parser::parse_if_stmt() {
    if (!assertToken(IF_KEYWORD, this)) return false;

    if (!boolean_expression()) return false;

    if (!assertToken(THEN_KEYWORD, this)) return false;

    int if_cond = file_pos;
    std::cout << "POS: " << if_cond << '\n';
    addInstruction(GOFALSE_OP, LITERAL_INTEGER, 0);
    file_pos++;

    int blk1 = file_pos;
    if (!parse_block()) return false;

    setInstruction(GOFALSE_OP, LITERAL_INTEGER, file_pos-blk1+1, if_cond);

    int else_cond = file_pos;
    addInstruction(GOTO_OP, NONE_TYPE, 0);
    file_pos++;

    if (!assertToken(ELSE_KEYWORD, this)) return false;

    int blk2 = file_pos;
    if (!parse_block()) return false;

    int jmp2 = file_pos;
    addInstruction(GOTO_OP, LITERAL_INTEGER, 0);
    file_pos++;
    setInstruction(GOTO_OP, LITERAL_INTEGER, file_pos-blk2, else_cond);

    if (!assertToken(END_KEYWORD, this)) return false;

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

    addInstruction(PRINT_OP, NONE_TYPE, 0);
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
      addInstruction(LE_OP, NONE_TYPE, 0);
      file_pos++;
    } else if (op.token == LT_OPERATOR) {
      addInstruction(LT_OP, NONE_TYPE, 0);
      file_pos++;
    } else if (op.token == GE_OPERATOR) {
      addInstruction(GE_OP, NONE_TYPE, 0);
      file_pos++;
    } else if (op.token == GT_OPERATOR) {
      addInstruction(GT_OP, NONE_TYPE, 0);
      file_pos++;
    } else if (op.token == EQ_OPERATOR) {
      addInstruction(EQ_OP, NONE_TYPE, 0);
      file_pos++;
    } else if (op.token == NE_OPERATOR) {
      addInstruction(NOT_EQ_OP, NONE_TYPE, 0);
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
    if (first_expr.token == ID) {
      int id_code = toupper(first_expr.lex[0]) - 'A';
      addInstruction(PUSH_OP, first_expr.token, id_code);
    } else if (first_expr.token == LITERAL_INTEGER) {
      char temp[first_expr.size];
      strncpy(temp, first_expr.lex, first_expr.size);
      temp[first_expr.size] = '\0';
      int val = atoi(temp);
      addInstruction(PUSH_OP, first_expr.token, val);
    } else {
      print_err_pos();
      std::cout << "Unexpected token. Expected an ID or Integer." << '\n';
      return false;
    }
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
      addInstruction(ADD_OP,NONE_TYPE,0);
      file_pos++;
    } else if(op.token == SUB_OPERATOR) {
      addInstruction(SUB_OP,NONE_TYPE,0);
      file_pos++;
    } else if(op.token == MULT_OPERATOR) {
      addInstruction(MULT_OP,NONE_TYPE,0);
      file_pos++;
    } else if(op.token == DIV_OPERATOR) {
      addInstruction(DIV_OP,NONE_TYPE,0);
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
    unsigned int val=0) {
      std::cout << "File POS: " << file_pos << "- ADD INSTR: " << instr << ":" << val_t << ":" << val << '\n';
      instr -= PUSH_OP;

      data->push_back((BYTE) instr);

      switch (val_t) {
        case 0:
          data->push_back((BYTE) 0);
          break;
        case ID:
          data->push_back((BYTE) 3);
          break;
        case LITERAL_INTEGER:
          data->push_back((BYTE) 2);
          break;
        default:
          print_err_pos();
          std::cout << "Incorrect type code" << '\n';
      }

      char c[4];

      c[0] = val & 0xFF;
      c[1] = (val>>8) & 0xFF;
      c[2] = (val>>16) & 0xFF;
      c[3] = (val>>24) & 0xFF;

      for (int i = 0; i < 4; i++) data->push_back((BYTE) c[i]);
  }

  void Parser::setInstruction(token_type instr, token_type val_t, unsigned int val, size_t pos) {
    //std::cout << "SET INSTR: " << instr << ":" << val_t << ":" << val << '\n';

    std::cout << "SIZE: " << data->size() << '\n';

    size_t byte_i = pos * 6;

    std::cout << "INSTRUCTIONS:";
    std::cout << (int) (*data)[byte_i] << ':';
    std::cout << (int) (*data)[byte_i+1] << ':';
    std::cout << (int) (*data)[byte_i+2] << ':';
    std::cout << (int) (*data)[byte_i+3] << ':';
    std::cout << (int) (*data)[byte_i+4] << ':';
    std::cout << (int) (*data)[byte_i+5] << '\n';

    instr -= PUSH_OP;
    (*data)[byte_i] = (BYTE) instr;

    switch (val_t) {
      case 0:
        (*data)[byte_i+1] = (BYTE) 0;
        break;
      case ID:
        (*data)[byte_i+1] = (BYTE) 3;
        break;
      case LITERAL_INTEGER:
        (*data)[byte_i+1] = (BYTE) 2;
        break;
      default:
        print_err_pos();
        std::cout << "Incorrect type code" << '\n';
    }

    char c[4];

    c[0] = val & 0xFF;
    c[1] = (val>>8) & 0xFF;
    c[2] = (val>>16) & 0xFF;
    c[3] = (val>>24) & 0xFF;

    for (int i = 0; i < 4; i++) (*data)[byte_i+2+i] = (BYTE) c[i];
  };

};
