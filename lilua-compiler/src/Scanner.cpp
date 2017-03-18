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
#include <cassert>
#include <string.h>
#include <string>
#include <cctype>
#include "Scanner.h"
#include "lilua_symbol.h"

namespace lilua_interpreter_project {

  // The Keyword table of all keywords in the subset of lua language
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

    // Checks to see if the input file is valid
    if (sourceFile->fail()) {
      fnf_flag = true;
      std::cout << "Failed to open file..." << '\n';
      sourceFile->clear();
    }

    // Initializes default values for data members
    err_flag = false;
    eof_flag = false;
    line_n = 0;
    prev_col_n = 0;
    col_n = 0;
    lex_len = 0;
    total_char = 0;
    current_token = UNKNOWN_TOKEN;
    input_line = new std::string();
    getNewLine();
  }

  Scanner::~Scanner() {
    delete sourceFile;
    delete input_line;
  }

  TOKEN Scanner::lex() {
    char c, n;
    int index = 0;
    current_token = UNKNOWN_TOKEN;

    memset (current_lexeme,' ',10);

    // Keep getting new characters from the file until getChar() will return a
    // non-whitespace character.
    skipWhitespace();

    if (eof()) return (TOKEN) {EOF_TOKEN, '\0'};

    do {
      c = getChar();

      // Conditional structure to test the current character
      if (std::isalpha(c)) {
        if (current_token == ID) {
          current_token = UKNOWN_KEYWORD;
        } else if (current_token != UKNOWN_KEYWORD) {
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
      } else if (c == '(') {
        current_token = LEFT_PAREN_TOKEN;
      } else if (c == ')') {
        current_token = RIGHT_PAREN_TOKEN;
      } else if (c == -1) {
        break;
      }

      // Append the current character to the LEXEME's string of characters
      current_lexeme[index++] = c;

      n = peekChar();
      if (isParen(c) || isParen(n) || isWhitespace(n)) break;

    } while(!isWhitespace(c));

    // If the lexical analysis process found a keyword, we need to figure out
    // what keyword it is.
    if (current_token == UKNOWN_KEYWORD) {
      // Create a temp string of the same size and characters as the current
      // lexeme.
      std::string temp(current_lexeme, index);

      // Get the token code of the keyword
      current_token = keyword_bin_search(temp.c_str());
    }

    TOKEN nextToken;
    nextToken.token = current_token;
    strcpy(nextToken.lex, current_lexeme);

    return nextToken;
  }

  char Scanner::getChar() {
    assert(input_line != NULL);
    if (eof_flag) return -1;
    char temp = *line_ptr;
    if (line_ptr < input_line->end()) ++line_ptr;
    else getNewLine();
    return temp;
  }

  char Scanner::peekChar() {
    assert(input_line != NULL);
    return *line_ptr;
  }

  bool Scanner::isWhitespace(char c) {
    return std::iscntrl(c) || std::isspace(c);
  }

  void Scanner::skipWhitespace() {
    assert(input_line != NULL);
    char c;
    c = peekChar();
    while (isWhitespace(c)){
      c = getChar();
      if (c == -1) return;
      c = peekChar();
    }
  }

  bool isParen(char c) {
    return c == '(' || c == ')';
  }

  void Scanner::getNewLine() {
    if (sourceFile->eof()) {
      eof_flag = true;
      if (sourceFile->is_open()) sourceFile->close();
      return;
    }
    getline(*sourceFile, *input_line);
    line_ptr = input_line->begin();
    ++line_n;
  }

  token_type Scanner::evaluateChar(char c, token_type current_token, bool eol_flag) {
    // Conditional structure to test the current character
    if (std::isalpha(c)) {
      if (current_token == ID) {
        current_token = UKNOWN_KEYWORD;
      } else if (current_token != UKNOWN_KEYWORD) {
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
    } else if (c == '(') {
      current_token = LEFT_PAREN_TOKEN;
    } else if (c == ')') {
      current_token = RIGHT_PAREN_TOKEN;
    } else if (c == -1) {
      eol_flag = true;
      return current_token;
    }

    return current_token;
  }

  token_type keyword_bin_search(const char* key) {
    // Initialize bounds
    int begin = 0;
    int end = KEYWORD_SIZE - 1;

    // Keep iterating until the bounds are too small
    while (begin <= end) {

      // Find midpoint
      int mid = (begin + end) / 2;

      // Compare to see if the keyword comes before the current element
      int comp = strcmp(key, keywordTable[mid].name);

      // If the keyword comes before the current element, search inside elements
      // begin to mid-1. If the keyword comes after the current element, search
      // inside elements mid+1 to end. If keyword and current element are equal
      // return the token code of the current element.
      if (comp < 0) {
        end = mid - 1;
      } else if (comp > 0) {
        begin = mid + 1;
      } else {
        return keywordTable[mid].type;
      }
    }

    // Return -1 if the binary search cannot find the element
    return -1;
  }
};
