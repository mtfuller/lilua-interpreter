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
  // struct TOKEN
  // Contains the token code and the actual string of characters of a lexeme.
  // ===========================================================================
  struct TOKEN {
    token_type token;
    char lex[15];
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

    bool is_file_found() {return !fnf_flag;}

    // =========================================================================
    // TOKEN lex()
    // Returns a TOKEN (containing both a token and the actual string of chars)
    // of the next token in the scanner's input file.
    // =========================================================================
    TOKEN lex();

    // =========================================================================
    // TOKEN getCol()
    // Returns the current columb in the input file.
    // =========================================================================
    size_t getCol() {return distance(input_line->begin(),line_ptr);}

    // =========================================================================
    // TOKEN getLine()
    // Returns the current line of the input file.
    // =========================================================================
    size_t getLine() {return line_n;}

    // =========================================================================
    // TOKEN getLine()
    // Returns the current line of the input file.
    // =========================================================================
    bool eof() {return eof_flag;}


    // =========================================================================
    // char getChar()
    // Returns the next character in the input file. This function also moves
    // the file pointer to the next character.
    // Preconditions: input_line is not empty
    // Postconditions: The next character in the line is returned, -1 is
    // returned if the end of the line is reached. The iterator is moved.
    // =========================================================================
    char getChar();

    // =========================================================================
    // char peekChar()
    // Returns the next character in the input file. This function does NOT
    // move the file pointer to the next character.
    // Preconditions: input_line is not empty
    // Postconditions: The next character in the line is returned, -1 is
    // returned if the end of the line is reached. The iterator is NOT moved.
    // =========================================================================
    char peekChar();

    // ===========================================================================
    // bool isWhitespace(char c)
    // Returns true if the given character is a whitespace, which is a space, tab
    // or some other control character. Otherwise, it will return false.
    // ===========================================================================
    bool isWhitespace(char c);

    // =========================================================================
    // char skipWhitespace()
    // Returns the next non-whitespace character from the input file. If there
    // are no more characters, -1 is returned.
    // Preconditions: input_line is not empty
    // =========================================================================
    void skipWhitespace();

    // =========================================================================
    // void getNewLine()
    // Returns the next non-whitespace character from the input file. If there
    // are no more characters, -1 is returned.
    // Precondition: line_ptr has reached the end of the line.
    // =========================================================================
    void getNewLine();

    token_type evaluateChar(char c, token_type current_token, bool eol_flag);


private:
    // Used for reading the input file
    std::ifstream* sourceFile;

    // Flags to mark if an error or an endo-of-file is encountered
    bool err_flag, eof_flag, fnf_flag;

    // Retains the current token code of the lexeme being analyzed
    token_type current_token;

    // A string to hold the current lexeme being evaluated
    char current_lexeme[LEXEME_BUFFER_SIZE];

    // Data members used to keep track of the location in the file stream
    unsigned int line_n, col_n, lex_len, prev_col_n, total_char;

    TOKEN curr_token;

    std::string::iterator line_ptr;
    std::string *input_line;

  };
};

#endif
