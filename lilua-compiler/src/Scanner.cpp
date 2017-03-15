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
#include <string.h>
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
      std::cout << "Failed to open file..." << '\n';
      sourceFile->clear();
    }

    // Initializes default values for data members
    err_flag = false;
    eof_flag = false;
    current_token = UNKNOWN_TOKEN;
  }

  Scanner::~Scanner() {
    delete sourceFile;
  }

  LEXEME Scanner::lex() {
    char c, n;
    int index = 0;
    current_token = UNKNOWN_TOKEN;

    // Erase the contents of current_lexeme
    memset (current_lexeme,' ',LEXEME_BUFFER_SIZE);

    // Keep getting new characters from the file until getChar() will return a
    // non-whitespace character.
    c = skipWhitespace();

    // Keep analyzing characters, one after another, until whitespace or
    // parenthesis are encountered.
    while (!isWhitespace(c)) {
      // Check if we have reached the end of file. If we have, close the input
      // file and return a EOF token
      if (eof_flag) {
        sourceFile->close();
        current_lexeme[0] = '\0';
        return (LEXEME) {EOF_TOKEN, current_lexeme};
      }

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
      }

      // Append the current character to the LEXEME's string of characters
      current_lexeme[index++] = c;

      n = peekChar();
      if (isParen(c) || isParen(n) || isWhitespace(n)) break;

      // Get the next character
      c = getChar();
    }



    // If the lexical analysis process found a keyword, we need to figure out
    // what keyword it is.
    if (current_token == UKNOWN_KEYWORD) {
      // Create a temp string of the same size and characters as the current
      // lexeme.
      std::string temp(current_lexeme, index);

      // Get the token code of the keyword
      current_token = keyword_bin_search(temp.c_str());


    }

    // Return the LEXEME's token code and character string
    return (LEXEME) {current_token, current_lexeme};
  }

  char Scanner::getChar() {
    char c;
    // If the file stream cannot get a new character, we have reached the EOF
    if (!sourceFile->get(c)) eof_flag = true;
    return c;
  }

  char Scanner::peekChar() {
    char c = sourceFile->peek();
    return c;
  }

  char Scanner::skipWhitespace() {
    char c;
    do {
      c = getChar();
      if (eof_flag) return -1;
    } while (isWhitespace(c));
    return c;
  }

  bool isWhitespace(char c) {
    return std::iscntrl(c) || std::isspace(c);
  }

  bool isParen(char c) {
    return c == '(' || c == ')';
  }

  token_type keyword_bin_search(const char* key) {
    // Initialize bounds
    size_t begin = 0;
    size_t end = KEYWORD_SIZE - 1;

    // Keep iterating until the bounds are too small
    while (begin <= end) {

      // Find midpoint
      size_t mid = (begin + end) / 2;

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
