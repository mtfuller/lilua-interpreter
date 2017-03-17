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
    bool eol_flag = false;
    int index = 0;
    current_token = UNKNOWN_TOKEN;

    //if (line_ptr == input_line->end()) getNewLine();

    // Erase the contents of current_lexeme
    memset (current_lexeme,' ',LEXEME_BUFFER_SIZE);

    std::cout << "DISTANCE: " << distance(line_ptr, input_line->end()) << '\n';


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
        return (TOKEN) {EOF_TOKEN, current_lexeme};
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
      } else if (c == -1) {
        eol_flag = true;
        break;
      }

      // Append the current character to the LEXEME's string of characters
      current_lexeme[index++] = c;

      n = peekChar();
      if (isParen(c) || isParen(n) || isWhitespace(n)) break;
      // Get the next character
      c = getChar();
    }

    if (eol_flag || line_ptr == input_line->end()) getNewLine();

    // If the lexical analysis process found a keyword, we need to figure out
    // what keyword it is.
    if (current_token == UKNOWN_KEYWORD) {
      // Create a temp string of the same size and characters as the current
      // lexeme.
      std::string temp(current_lexeme, index);

      // Get the token code of the keyword
      current_token = keyword_bin_search(temp.c_str());
    }

    if (current_token == -1) {
      return (TOKEN) {ERR_TOKEN, "\0"};
    }

    // Return the LEXEME's token code and character string
    return (TOKEN) {current_token, current_lexeme};
  }

  TOKEN Scanner::peekLex() {
    std::streampos initial_file_pos = sourceFile->tellg();
    unsigned int initial_line = line_n;
    size_t initial_col = getCol();
    std::string::iterator initial_line_pos = line_ptr;

    TOKEN next = lex();

    if (initial_line == line_n) {
      line_ptr = initial_line_pos;
    } else {
      sourceFile->seekg (initial_file_pos);
      line_n = initial_line;
      for (size_t i = 0; i < initial_col; i++) ++line_ptr;
    }
    return next;
  }

  char Scanner::getChar() {
    assert(input_line != NULL);
    char temp = *line_ptr;
    if (line_ptr < input_line->end()) ++line_ptr;
    else {
      line_ptr = input_line->end();
      return -1;
    }
    return temp;
  }

  char Scanner::peekChar() {
    assert(input_line != NULL);
    return *line_ptr;
  }

  bool Scanner::isWhitespace(char c) {
    return std::iscntrl(c) || std::isspace(c);
  }

  char Scanner::skipWhitespace() {
    assert(input_line != NULL);
    char c;
    do {
      c = getChar();
      if (eof_flag) return -1;
    } while (isWhitespace(c));
    return c;
  }

  bool isParen(char c) {
    return c == '(' || c == ')';
  }

  void Scanner::getNewLine() {
    assert(line_ptr <= input_line->end());
    getline(*sourceFile, *input_line);
    line_ptr = input_line->begin();
    ++line_n;
    if (sourceFile->eof()) eof_flag = true;
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
