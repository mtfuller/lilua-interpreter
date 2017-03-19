// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 5 - 2nd Deliverable
// File:      Parser.cpp
// =============================================================================
// Description:
// This file is the implementation of the parser class.
// =============================================================================

#include <iostream>         // Console ouput
#include <fstream>          // File I/O
#include <string.h>         // strncpy() function
#include <stdlib.h>         // atoi() function
#include "Parser.h"

namespace lilua_interpreter_project {
  const std::string token_string_arr[] = {
    "EOF","UNKNOWN_TOKEN","LEFT_PAREN_TOKEN","RIGHT_PAREN_TOKEN","ID",
    "LITERAL_INTEGER","ASSIGNMENT_OPERATOR","LE_OPERATOR","LT_OPERATOR",
    "GE_OPERATOR","GT_OPERATOR","EQ_OPERATOR","NE_OPERATOR","ADD_OPERATOR",
    "SUB_OPERATOR","MULT_OPERATOR","DIV_OPERATOR","NULL_KEYWORD","DO_KEYWORD",
    "ELSE_KEYWORD","END_KEYWORD","FUNCTION_KEYWORD","IF_KEYWORD","PRINT_KEYWORD",
    "REPEAT_KEYWORD","THEN_KEYWORD","UNTIL_KEYWORD","WHILE_KEYWORD"
  };

  int get_token_string_index(token_type token_code) {
    return token_code + 1;
  }

  bool isStatement(const TOKEN lex) {
    return lex.token == ID || lex.token == IF_KEYWORD ||
    lex.token == PRINT_KEYWORD || lex.token == REPEAT_KEYWORD ||
    lex.token == WHILE_KEYWORD;
  }

  void int_to_bytes(BYTE* byteArr, const int val) {
    for (int i = 0; i < 4; i++) byteArr[i] = (val>>(8*i)) & 0xFF;
  }

  bool assertToken(const token_type expectedCode, Parser* parser) {
    TOKEN token = parser->getToken();

    // Check if the next token matches what was expected
    if (token.token == expectedCode) return true;
    else {
      parser->print_err_pos();
      std::cout << "Unexpected token. Expected \"" << token_string_arr[get_token_string_index(expectedCode)] << "\"\n";
    }
    return false;
  }

  Parser::Parser(const char *source_file, const char *output_file) {
    // Create new scanner for the specified input source file
    lexicalAnalyzer = new Scanner(source_file);

    // Record the specified source and output paths for future use.
    sourcePath = new std::string(source_file);
    outputPath = new std::string(output_file);

    // Create BYTE vector to store instruction codes
    data = new std::vector<BYTE>;

    // Initializing file position
    file_pos = 0;
  }

  Parser::~Parser() {
    delete lexicalAnalyzer;
    delete outputFile;
    delete sourcePath;
    delete outputPath;
    delete data;
  }

  bool Parser::parse() {
    // See if source file exists
    if (lexicalAnalyzer->is_file_found()) {

      // Get first token and update source line and columb
      source_line_n = lexicalAnalyzer->getLineNumber();
      source_col_n = lexicalAnalyzer->getColNumber();
      current = lexicalAnalyzer->lex();

      // Run parse program
      if (parse_prgm()) {
        std::cout << "SUCCESS!!!" << '\n';

        // Create a binary output file stream to the specified output file path
        outputFile = new std::ofstream(outputPath->c_str(), std::ios::binary);

        // Initializing some important variables for file IO
        size_t size = data->size();
        size_t index = 0;

        // Create new array to hold each byte to be written to the output file
        BYTE memdata[size];

        // Walk through the BYTE vector to get each byte used in the instruction
        // code
        for (std::vector<BYTE>::iterator it = data->begin(); it != data->end(); ++it)
            memdata[index++] = (BYTE) *it;

        // Write to the output file
        outputFile->write(memdata,size);
        outputFile->close();

        // Success message
        std::cout << "Successfully created file \"" << *outputPath << "\" (" <<
          size << " Bytes)" << '\n';

        return true;
      } else {
        // Close the Scanner's input file
        lexicalAnalyzer->close();

        // Get line and columb information
        size_t l = lexicalAnalyzer->getLineNumber();
        size_t c = lexicalAnalyzer->getColNumber()-1;

        // Open Scanner's input file
        std::ifstream src(sourcePath->c_str());

        // Walk through file until the specific line is found
        std::string line;
        for (size_t i = 0; i < l; i++) getline(src, line);
        src.close();              // !!! Close the file

        // Build a string to "point" to the specific columb in the line
        std::string carrot;
        for (size_t i = 0; i < c-1; i++) carrot.append(" ");
        carrot.append("^");       // Add carrot to the end of the string

        // Output the line that contains the parsing error
        std::cout << line << '\n';
        std::cout << carrot << '\n';

        // Parsing Error Message
        std::cout << "Encountered a Parsing Error. Unable to create " <<
          "compiled LiLua file." << '\n';
      }
    } else {
      // File Not Found Error Message
      std::cout << "File Not Found ERROR: Cannot locate \"" << *sourcePath <<
        "\".\n";
    }

    return false;
  }

  bool Parser::eof() {
    return lexicalAnalyzer->eof();
  }

  bool Parser::parse_prgm() {
    // Assert the first few tokens in the <program> syntax rule are correct
    if (!assertToken(FUNCTION_KEYWORD, this)) return false;
    if (!assertToken(ID, this)) return false;
    if (!assertToken(LEFT_PAREN_TOKEN, this)) return false;
    if (!assertToken(RIGHT_PAREN_TOKEN, this)) return false;

    // Parse the <block> non-terminal
    if (!parse_block()) return false;

    // Assert that there is an END keyword after the <block>
    if (!assertToken(END_KEYWORD, this)) return false;

    // Add the HALT instruction to the BYTE vector, to be added to the output
    // file later.
    addInstruction(HALT_OP, NONE_TYPE, 0);

    return true;
  }

  bool Parser::parse_block() {
    // Parse the <statement> non-terminal
    if (!parse_statement()) return false;

    // See if there is another possible statement, and if so, run parse block
    // again
    TOKEN next = nextToken();
    if (isStatement(next)) if (!parse_block()) return false;

    return true;
  }

  bool Parser::parse_statement() {
    // Get next token and determine which statement it belongs to, and then
    // parse that type of statement
    TOKEN next = nextToken();
    if (next.token == ID) return parse_assignment_stmt();
    else if (next.token == IF_KEYWORD) return parse_if_stmt();
    else if (next.token == PRINT_KEYWORD) return parse_print_stmt();
    else if (next.token == WHILE_KEYWORD) return parse_while_stmt();
    else if (next.token == REPEAT_KEYWORD) return parse_repeat_stmt();
    else if (next.token == END_KEYWORD) return true;
    else return false;
  }

  bool Parser::parse_assignment_stmt() {
    // Get next token and verify that it is an ID
    TOKEN id = getToken();
    if (id.token != ID) {
      std::cout << "Unexpected token. Expected an ID, but received a\"" << token_string_arr[get_token_string_index(id.token)] << "\"." << '\n';
      return false;
    }

    // Add a PUSH instruction to the data vector
    int id_code = toupper(id.lex[0]) - 'A';
    addInstruction(PUSH_OP, id.token, id_code);

    // Assert that the next token is an ASSIGNMENT OPERATOR
    if (!assertToken(ASSIGNMENT_OPERATOR, this)) return false;

    // Parse the <arithmetic_expression> non-terminal
    if (!arithmetic_expression()) return false;

    // Add an ASSIGN instruction to the data vector
    addInstruction(ASSIGN_OP, NONE_TYPE, 0);

    return true;
  }

  bool Parser::parse_if_stmt() {
    // Assert that the next token is an IF keyword
    if (!assertToken(IF_KEYWORD, this)) return false;

    // Parse the <boolean_expression> non-terminal
    if (!boolean_expression()) return false;

    // Assert that the next token is an THEN keyword
    if (!assertToken(THEN_KEYWORD, this)) return false;

    // Add GOFALSE instruction, and record its location in the data vector
    int gofalse_instr = file_pos;
    addInstruction(GOFALSE_OP, LITERAL_INTEGER, 0);

    // Record begnning location of the true block, and then parse the <block>
    // non-terminal
    int true_blk = file_pos;
    if (!parse_block()) return false;

    // Revise the first GOFALSE instruction with the number of instructions to
    // skip over.
    setInstruction(GOFALSE_OP, LITERAL_INTEGER, file_pos-true_blk+1,
      gofalse_instr);

    // Add GOTO instruction, and record its location in the data vector
    int goto_instr = file_pos;
    addInstruction(GOTO_OP, NONE_TYPE, 0);

    // Assert that the next token is an ELSE keyword
    if (!assertToken(ELSE_KEYWORD, this)) return false;

    // Record begnning location of the false block, and then parse the <block>
    // non-terminal
    int false_blk = file_pos;
    if (!parse_block()) return false;

    // Add GOTO instruction after the else block
    addInstruction(GOTO_OP, LITERAL_INTEGER, 0);

    // Revise the first GOTO instruction with the number of instructions to
    // skip over.
    setInstruction(GOTO_OP, LITERAL_INTEGER, file_pos-false_blk, goto_instr);

    // Assert that the next token is an END keyword
    if (!assertToken(END_KEYWORD, this)) return false;

    return true;
  }

  bool Parser::parse_while_stmt() {
    // Assert that the next token is a WHILE keyword
    if (!assertToken(WHILE_KEYWORD, this)) return false;

    // Record beginning location of the while statement, and parse the
    // <boolean_expression> non-terminal
    int begin = file_pos;
    if (!boolean_expression()) return false;

    // Assert that the next token is a DO keyword
    if (!assertToken(DO_KEYWORD, this)) return false;

    // Add GOFALSE instruction, and record its location in the data vector
    int gofalse = file_pos;
    addInstruction(GOFALSE_OP, LITERAL_INTEGER, 0);

    // Parse <block> non-terminal
    if (!parse_block()) return false;

    // Assert that the next token is an END keyword
    if (!assertToken(END_KEYWORD, this)) return false;

    // Add GOTO instruction to return the instruction pointer to beginning of
    // loop
    addInstruction(GOTO_OP, LITERAL_INTEGER, begin-file_pos-1);

    // Revise the GOFALSE instruction with the number of instructions to
    // skip over.
    setInstruction(GOFALSE_OP, LITERAL_INTEGER, file_pos-gofalse-1, gofalse);

    return true;
  }

  bool Parser::parse_repeat_stmt() {
    // Assert that the next token is a REPEAT keyword
    if (!assertToken(REPEAT_KEYWORD, this)) return false;

    // Record beginning location of statement, and then parse <block>
    // non-terminal
    int begin = file_pos;
    if (!parse_block()) return false;

    // Assert that the next token is an UNTIL keyword
    if (!assertToken(UNTIL_KEYWORD, this)) return false;

    // Parse <boolean_expression> non-terminal
    if (!boolean_expression()) return false;

    // Add GOFALSE instruction to repeat the loop
    addInstruction(GOFALSE_OP, LITERAL_INTEGER, begin-file_pos-1);

    return true;
  }

  bool Parser::parse_print_stmt() {
    // Assert that the next few tokens are correct
    if (!assertToken(PRINT_KEYWORD, this)) return false;
    if (!assertToken(LEFT_PAREN_TOKEN, this)) return false;

    // Parse the <arithmetic_expression> non-terminal
    if (!arithmetic_expression()) return false;

    // Assert that the last token is correct
    if (!assertToken(RIGHT_PAREN_TOKEN, this)) return false;

    // Add Print instruction to data vector
    addInstruction(PRINT_OP, NONE_TYPE, 0);

    return true;
  }

  bool Parser::boolean_expression() {
    // Parse the <arithmetic_expression> non-terminal
    if (!arithmetic_expression()) return false;

    // Get operator token
    TOKEN op = getToken();

    // Parse the <arithmetic_expression> non-terminal
    if (!arithmetic_expression()) return false;

    // Parse the <relative_op> non-terminal
    if (!relative_op(op)) return false;

    return true;
  }

  bool Parser::relative_op(const TOKEN op) {
    // Checks which operator op belongs to, and then adds its corresponding
    // instruction
    if (op.token == LE_OPERATOR) {
      addInstruction(LE_OP, NONE_TYPE, 0);
    } else if (op.token == LT_OPERATOR) {
      addInstruction(LT_OP, NONE_TYPE, 0);
    } else if (op.token == GE_OPERATOR) {
      addInstruction(GE_OP, NONE_TYPE, 0);
    } else if (op.token == GT_OPERATOR) {
      addInstruction(GT_OP, NONE_TYPE, 0);
    } else if (op.token == EQ_OPERATOR) {
      addInstruction(EQ_OP, NONE_TYPE, 0);
    } else if (op.token == NE_OPERATOR) {
      addInstruction(NOT_EQ_OP, NONE_TYPE, 0);
    } else {
      print_err_pos();
      std::cout << "Invalid boolean operator." << '\n';
      return false;
    }
    return true;
  }

  bool Parser::arithmetic_expression() {
    // Get first expression and checks if its an ID or LITERAL_INTEGER
    TOKEN first_expr = getToken();
    if (first_expr.token == ID) {
      // Adds PUSH instruction for ID
      int id_code = toupper(first_expr.lex[0]) - 'A';
      addInstruction(PUSH_OP, first_expr.token, id_code);
    } else if (first_expr.token == LITERAL_INTEGER) {
      // Create a char array representation of the literal integer
      char temp[first_expr.size];
      strncpy(temp, first_expr.lex, first_expr.size);
      temp[first_expr.size] = '\0';

      // Converts the char array to a number, and adds a PUSH instruction for
      // the evaluated LITERAL INTEGER
      int val = atoi(temp);
      addInstruction(PUSH_OP, first_expr.token, val);
    } else {
      print_err_pos();
      std::cout << "Unexpected token. Expected an ID or Integer." << '\n';
      return false;
    }

    // Check if the next token is an arithmetic operator, and if so, parses
    // another <arithmetic_expression> non-terminal
    TOKEN next = nextToken();
    if (next.token == ADD_OPERATOR || next.token == SUB_OPERATOR ||
        next.token == MULT_OPERATOR || next.token == DIV_OPERATOR) {
          // Get operator token
          TOKEN op = getToken();

          // Parse the next two non-terminals
          if (!arithmetic_expression()) return false;
          if (!arithmetic_op(op)) return false;
    }

    return true;
  }

  bool Parser::arithmetic_op(const TOKEN op) {
    // Checks which operator op belongs to, and then adds its corresponding
    // instruction
    if (op.token == ADD_OPERATOR) {
      addInstruction(ADD_OP,NONE_TYPE,0);
    } else if(op.token == SUB_OPERATOR) {
      addInstruction(SUB_OP,NONE_TYPE,0);
    } else if(op.token == MULT_OPERATOR) {
      addInstruction(MULT_OP,NONE_TYPE,0);
    } else if(op.token == DIV_OPERATOR) {
      addInstruction(DIV_OP,NONE_TYPE,0);
    } else {
      print_err_pos();
      std::cout << "Invalid boolean operator." << '\n';
      return false;
    }
    return true;
  }

  void Parser::print_err_pos() const {
    std::cout << "ERROR:" << source_line_n << ":" <<
      source_col_n+1 << ": ";
  }

  TOKEN Parser::getToken() {
    TOKEN temp = current;

    // Get next token from scanner, and updates source line and columb info
    source_line_n = lexicalAnalyzer->getLineNumber();
    source_col_n = lexicalAnalyzer->getColNumber();
    current = lexicalAnalyzer->lex();

    return temp;
  }

  TOKEN Parser::nextToken() {
    return current;
  }

  void Parser::addInstruction(token_type instr=0, token_type val_t=0,
    unsigned int val=0) {
      // Compute and add INSTRUCTION code to data vector
      instr -= PUSH_OP;
      data->push_back((BYTE) instr);

      // Compute and add TYPE code to data vector
      switch (val_t) {
        case 0:
          data->push_back((BYTE) 0);
          break;
        case ID:
          data->push_back((BYTE) 3);
          break;
        case LITERAL_INTEGER:
          data->push_back((BYTE) 2);
          break;
        default:
          print_err_pos();
          std::cout << "Incorrect type code" << '\n';
      }

      // Compute and add VALUE code to data vector
      BYTE bytes[4];
      int_to_bytes(bytes, val);
      for (int i = 0; i < 4; i++) data->push_back((BYTE) bytes[i]);

      // Increase current location in data vector
      file_pos++;
  }

  void Parser::setInstruction(token_type instr, token_type val_t, unsigned int val, size_t pos) {
    // Find the byte index using the current instruction location. Since every
    // instruction is 6 Bytes, the byte index will equal pos * 6;
    size_t byte_i = pos * 6;

    // Compute and add INSTRUCTION code to data vector
    instr -= PUSH_OP;
    (*data)[byte_i] = (BYTE) instr;

    // Compute and add TYPE code to data vector
    switch (val_t) {
      case 0:
        (*data)[byte_i+1] = (BYTE) 0;
        break;
      case ID:
        (*data)[byte_i+1] = (BYTE) 3;
        break;
      case LITERAL_INTEGER:
        (*data)[byte_i+1] = (BYTE) 2;
        break;
      default:
        print_err_pos();
        std::cout << "Incorrect type code" << '\n';
    }

    // Compute and add VALUE code to data vector
    BYTE bytes[4];
    int_to_bytes(bytes, val);
    for (int i = 0; i < 4; i++) (*data)[byte_i+2+i] = (BYTE) bytes[i];
  };

};
