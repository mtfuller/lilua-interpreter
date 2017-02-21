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

#include <fstream>         // Used for file input
#include "lilua_symbol.h"   // Symbol definitions

#define LEXEME_BUFFER_SIZE  100
#define KEYWORD_SIZE        10

namespace lilua_interpreter_project {
  typedef int token_type;

  struct LEXEME {
    token_type token;
    const char* lex;
  };

  struct KEYWORD {
    const char* name;
    token_type type;
  };

  bool isWhitespace(char c);
  token_type keyword_bin_search(const char* key);

  class Scanner {
  public:
    // =========================================================================
    // Constructors
    // =========================================================================
    Scanner (char *fileStr);
    ~Scanner ();
    // =========================================================================
    // Public Member Functions
    // =========================================================================
    LEXEME lex();
  private:
    // =========================================================================
    // Private Member Functions
    // =========================================================================
    char getChar();
    char peekChar();
    // =========================================================================
    // Constant Member Functions
    // =========================================================================
    int keywordLookup(char *lex) const;
    // =========================================================================
    // Private Data Members
    // =========================================================================
    std::ifstream* sourceFile;
    bool err_flag, eof_flag;
    token_type current_token;
    char current_lexeme[LEXEME_BUFFER_SIZE];
  };
}

#endif
