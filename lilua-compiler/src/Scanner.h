// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 3 - 1st Deliverable
// File:      Scanner.h
// =============================================================================
// Description:
// This file includes functions and definitions that are used in the lexical
// analysis of an input file for a subset of Lua, defined in the Project
// Specification Document.
// =============================================================================

#ifndef _LILUA_SCANNER_H
#define _LILUA_SCANNER_H

#include <fstream>                // Used for file input
#include "lilua_symbol.h"         // Symbol definitions

#define LEXEME_BUFFER_SIZE  100   // The length of current_lexeme string
#define KEYWORD_SIZE        10    // The size of the keyword table

namespace lilua_interpreter_project {
  typedef int token_type;         // Data type used for all token codes

  // ===========================================================================
  // struct LEXEME
  // Contains the token code and the actual string of characters of a lexeme.
  // ===========================================================================
  struct LEXEME {
    token_type token;
    const char* lex;
  };

  // ===========================================================================
  // struct KEYWORD
  // Contains the name and type code for a given keyword.
  // ===========================================================================
  struct KEYWORD {
    const char* name;
    token_type type;
  };

  // ===========================================================================
  // bool isWhitespace(char c)
  // Returns true if the given character is a whitespace, which is a space, tab
  // or some other control character. Otherwise, it will return false.
  // ===========================================================================
  bool isWhitespace(char c);

  // ===========================================================================
  // bool isParen(char c)
  // Returns true if the given character is a left or right parenthesis.
  // ===========================================================================
  bool isParen(char c);

  // ===========================================================================
  // token_type keyword_bin_search(const char* key)
  // Returns the token code of the corresponding string "key". If the key is
  // invalid, it returns -1.
  // ===========================================================================
  token_type keyword_bin_search(const char* key);

  // ===========================================================================
  // Scanner
  // A class used to facillitate the majority of the lexical analysis. This
  // scanner class defines the lexical analysis for the subset of Lua defined
  // in the Project Specification Document.
  // ===========================================================================
  class Scanner {
  public:
    // =========================================================================
    // Constructors/Destructor
    // =========================================================================
    Scanner (const char *fileStr);
    ~Scanner ();

    // =========================================================================
    // Public Member Functions
    // =========================================================================

    // =========================================================================
    // LEXEME lex()
    // Returns a LEXEME (containing both a token and the actual string of chars)
    // of the next token in the scanner's input file.
    // =========================================================================
    LEXEME lex();

  private:
    // =========================================================================
    // char getChar()
    // Returns the next character in the input file. This function also moves
    // the file pointer to the next character.
    // =========================================================================
    char getChar();

    // =========================================================================
    // char peekChar()
    // Returns the next character in the input file. This function does NOT
    // move the file pointer to the next character.
    // =========================================================================
    char peekChar();

    // =========================================================================
    // char skipWhitespace()
    // Returns the next non-whitespace character from the input file. If there
    // are no more characters, -1 is returned.
    // =========================================================================
    char skipWhitespace();

    // Used for reading the input file
    std::ifstream* sourceFile;

    // Flags to mark if an error or an endo-of-file is encountered
    bool err_flag, eof_flag;

    // Retains the current token code of the lexeme being analyzed
    token_type current_token;

    // A string to hold the current lexeme being evaluated
    char current_lexeme[LEXEME_BUFFER_SIZE];
  };
}

#endif
