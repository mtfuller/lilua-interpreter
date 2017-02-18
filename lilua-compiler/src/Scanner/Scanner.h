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

namespace lilua_interpreter_project {
  typedef int token_type;

  struct LEXEME {
    token_type token;
    char lex;
  };

  struct KEYWORD {
    token_type type;
    const char *name;
  };

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
    static KEYWORD keywordTable[];
    // =========================================================================
    // Private Member Functions
    // =========================================================================
    char getChar();
    // =========================================================================
    // Constant Member Functions
    // =========================================================================
    int keywordLookup(char *lex) const;
    // =========================================================================
    // Private Data Members
    // =========================================================================
    std::ifstream* sourceFile;
    bool err_flag;
    token_type current_token;
    char current_lexeme[LEXEME_BUFFER_SIZE];
  };
}

#endif
