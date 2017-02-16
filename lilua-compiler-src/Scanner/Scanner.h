// =============================================================================
// Author(s): Thomas Fuller
// Project:   Module 3 - 1st Deliverable
// File:      Scanner.h
// =============================================================================
// Description:
//
// =============================================================================
#ifndef _LILUA_SCANNER_H
#define _LILUA_SCANNER_H

#include <ifstream>         // Used for file input
#include "lilua_symbol.h"   // Symbol definitions

#define LEXEME_BUFFER_SIZE  100

namespace lilua_interpreter_project {
  typedef unsigned int token_type;

  struct LEXEME {
    token_type token,
    const char *lex
  }

  struct KEYWORD {
    token_type type,
    const char *name
  }

  class Scanner {
  public:
    Scanner (std::ifstream& sourceFile);
    LEXEME lex() const;
  private:
    static KEYWORD keywordTable[];
    char getChar();
    int keywordLookup(char *lex) const;
    bool err_flag = false;
    token_type current_token = UNKNOWN_TOKEN;
    char current_lexeme[LEXEME_BUFFER_SIZE];
  };
}

#endif
