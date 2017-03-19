// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 5 - 2nd Deliverable
// File:      Parser.h
// =============================================================================
// Description:
// This file is the header file of the Parser class. All function and data
// memebers are defined below. Includes the Parser class, which is used as the
// main mechanism for syntax analysis on a given input file.
// =============================================================================

#ifndef _LILUA_PARSER_H
#define _LILUA_PARSER_H

#include <vector>                 // Used for data vector
#include "Scanner.h"              // Scanner
#include "lilua_symbol.h"         // Symbol definitions

namespace lilua_interpreter_project {
  typedef char BYTE;

  // ===========================================================================
  // bool isStatement(const TOKEN lex)
  // Returns true if the given TOKEN is a valid beginning to a statement in the
  // LiLua language (subset of Lua).
  // ===========================================================================
  bool isStatement(const TOKEN lex);

  // ===========================================================================
  // void int_to_bytes(BYTE* byteArr, const int val)
  // Takes in a 32-bit integer and converts it to 4 bytes (BYTE) and then adds
  // each byte into byteArr.
  // ===========================================================================
  void int_to_bytes(BYTE* byteArr, const int val);

  class Parser {
  public:
    // =========================================================================
    // Constructor/Destructor
    // =========================================================================

    // =========================================================================
    // Parser(const char *sourceFile, const char *outputFile)
    // Takes in two strings, one for the source file to be evaluated, and the
    // other for the output file which will hold the instruction codes for the
    // interpreter.
    // =========================================================================
    Parser(const char *sourceFile, const char *outputFile);

    ~Parser();

    // =========================================================================
    // Public Member Functions
    // =========================================================================

    // =========================================================================
    // bool parse()
    // Attempts to parse the given input file, and then output the corresponding
    // instruction codes to the specified output file. Returns true if the
    // process was successful.
    // =========================================================================
    bool parse();

    // =========================================================================
    // bool eof()
    // Returns true if the end of file has been reached in the source file.
    // =========================================================================
    bool eof();

  private:
    // =========================================================================
    // Private Member Functions
    // =========================================================================

    // =========================================================================
    // TOKEN getToken()
    // Returns the current token in the source file, and then moves the cursor
    // to the next position in the source file.
    // =========================================================================
    TOKEN getToken();

    // =========================================================================
    // TOKEN nextToken()
    // Returns the next token in the source file, but does not move the file
    // cursor.
    // =========================================================================
    TOKEN nextToken();

    // =========================================================================
    // Internal Parsing Functions
    //
    // Description:
    // Each of the following functions were used to parse their corresponding
    // syntax rule. These functions used a recursive-decent parsing method
    // in order to evaluate the sequence of tokens from the scanner. For
    // example, the parse_prgm() would call the parse_block(), which would call
    // the parse_statement(). The parse_statement() would could then call
    // parse_assignment_stmt() or parse_while_stmt(), depending on the next
    // token.
    //
    // Several functions add instruction codes to the data vector, to be later
    // written to a file. These instruction codes range from PUSH, POP, ASSIGN,
    // PRINT, GOFALSE, GOTO, etc. For more information on instruction codes,
    // please consult the repo's wiki.
    // =========================================================================
    bool parse_prgm();
    bool parse_block();
    bool parse_statement();
    bool parse_assignment_stmt();
    bool parse_if_stmt();
    bool parse_while_stmt();
    bool parse_repeat_stmt();
    bool parse_print_stmt();
    bool boolean_expression();
    bool arithmetic_expression();
    bool relative_op(const TOKEN op);
    bool arithmetic_op(const TOKEN op);

    // =========================================================================
    // void print_err_pos() const
    // Prints the current line and columb number of the scanner to the console.
    // =========================================================================
    void print_err_pos() const;

    // =========================================================================
    // void addInstruction(token_type instr, token_type val_t, unsigned int val)
    //
    // Adds the specified instruction code to the data vector. The instr
    // parameter takes in OP CODES for each instruction (ranging from 5000 -
    // 5016). The val_t parameter takes in the token code, NOT the instruction
    // type code. The val parameter is just an int to specify the VALUE section
    // of the instruction.
    //
    // Instruction codes follow the format in a file:
    // [OP (1 BYTE)] | [TYPE (1 BYTE)] | [VALUE (4 BYTES)]
    // =========================================================================
    void addInstruction(token_type instr, token_type val_t, unsigned int val);

    // =========================================================================
    // void setInstruction(token_type instr, token_type val_t, unsigned int val,
    //   size_t pos)
    //
    // Sets the instruction code at pos to a specified instruction. Same format
    // of the addInstruction() function, but the pos parameter selects which
    // instruction to overwrite.
    // =========================================================================
    void setInstruction(token_type instr, token_type val_t, unsigned int val,
      size_t pos);

    // =========================================================================
    // friend bool assertToken(const token_type expectedCode, Parser* parser)
    // Returns true if the next token in the source file matches the expected
    // token denoted in the expectedCode parameter. Returns false otherwise.
    // =========================================================================
    friend bool assertToken(const token_type expectedCode, Parser* parser);

    // =========================================================================
    // Private Data Members
    // =========================================================================

    // The current token being evaluated
    TOKEN current;

    // Used for lexical analyzing the given source file
    Scanner *lexicalAnalyzer;

    // Strings that represent the file paths for the source and output file
    std::string *sourcePath, *outputPath;

    // The output file stream used for writing the instruction codes to the
    // output file
    std::ofstream *outputFile;

    // Used to store the bytes to be written to the output file
    std::vector<BYTE>* data;

    // Used to store the current, logical instruction index in the data vector
    size_t file_pos;

    // Used to store the current source line and columb information
    size_t source_line_n, source_col_n;
  };

};

#endif
