// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 3 - 1st Deliverable
// File:      Scanner.cpp
// =============================================================================
// Description:
//
// =============================================================================
#include <iostream>
#include <string.h>
#include <cctype>
#include "Scanner.h"
#include "lilua_symbol.h"

namespace lilua_interpreter_project {
  KEYWORD keywordTable[] = {
    {"do",DO_KEYWORD},
    {"else",ELSE_KEYWORD},
    {"end",END_KEYWORD},
    {"function",FUNCTION_KEYWORD},
    {"if",IF_KEYWORD},
    {"print",PRINT_KEYWORD},
    {"repeat",REPEAT_KEYWORD},
    {"then",THEN_KEYWORD},
    {"until",UNTIL_KEYWORD},
    {"while",WHILE_KEYWORD}
  };

  Scanner::Scanner(const char *file) {
    sourceFile = new std::ifstream(file);
    if (sourceFile->fail()) {
      std::cout << "Failed to open file..." << '\n';
      sourceFile->clear();
    }
    err_flag = false;
    eof_flag = false;
    current_token = UNKNOWN_TOKEN;
  }

  Scanner::~Scanner() {
    delete sourceFile;
  }

  LEXEME Scanner::lex() {
    char c, n;
    unsigned int index = 0;
    current_token = UNKNOWN_TOKEN;

    memset (current_lexeme,' ',LEXEME_BUFFER_SIZE);

    while (isWhitespace(peekChar())) c = getChar();

    do {
      c = getChar();

      if (eof_flag) {
        sourceFile->close();
        current_lexeme[0] = '\0';
        return (LEXEME) {EOF_TOKEN, current_lexeme};
      }

      if (std::isalpha(c)) {
        if (current_token == ID) {
          current_token = NULL_KEYWORD;
        } else if (current_token != NULL_KEYWORD) {
          current_token = ID;
        }
      } else if (std::isdigit(c)) {
        current_token = LITERAL_INTEGER;
      } else if (c == '=') {
        if (current_token == UNKNOWN_TOKEN) {
          current_token = ASSIGNMENT_OPERATOR;
        } else if (current_token == ASSIGNMENT_OPERATOR) {
          current_token = EQ_OPERATOR;
        } else if (current_token == LT_OPERATOR) {
          current_token = LE_OPERATOR;
        } else if (current_token == GT_OPERATOR) {
          current_token = GE_OPERATOR;
        }
      } else if (c == '<') {
        current_token = LT_OPERATOR;
      } else if (c == '>') {
        current_token = GT_OPERATOR;
      } else if (c == '+') {
        current_token = ADD_OPERATOR;
      } else if (c == '-') {
        current_token = SUB_OPERATOR;
      } else if (c == '*') {
        current_token = MULT_OPERATOR;
      } else if (c == '/') {
        current_token = DIV_OPERATOR;
      } else {
        current_token = UNKNOWN_TOKEN;
      }

      current_lexeme[index++] = c;

      n = peekChar();
      if (n == '(' || n == ')' || c == '(' || c == ')' || isWhitespace(n)) break;
    } while (!isWhitespace(c));

    if (current_token == NULL_KEYWORD) {
      std::string temp(current_lexeme, index);
      current_token = keyword_bin_search(temp.c_str());
    }

    return (LEXEME) {current_token, current_lexeme};
  }

  char Scanner::getChar() {
    char c;
    if (!sourceFile->get(c)) eof_flag = true;
    return c;
  }

  char Scanner::peekChar() {
    char c = sourceFile->peek();
    return c;
  }

  bool isWhitespace(char c) {
    return std::iscntrl(c) || std::isspace(c);
  }

  token_type keyword_bin_search(const char* key) {
    size_t begin = 0;
    size_t end = KEYWORD_SIZE - 1;
    while (begin <= end) {
      size_t mid = (begin + end) / 2;
      int comp = strcmp(key, keywordTable[mid].name);
      if (comp < 0) {
        end = mid - 1;
      } else if (comp > 0) {
        begin = mid + 1;
      } else {
        return keywordTable[mid].type;
      }
    }
    return -1;
  }
};
